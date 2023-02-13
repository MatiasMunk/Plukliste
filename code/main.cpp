#include <conio.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#ifdef WIN32
#include <windows.h> //For Windows Directory manipulation
#elif UNIX
#include <limits.h> //Linux MAX_PATH
#include <dirent.h> //Linux Directory manipulation
#endif

#include <nlohmann/json.hpp>

#define MAX_DIRECTORY_PATH_LENGTH MAX_PATH //Define macro with different name, due to the fact that MAX_PATH is ambiguous

using json = nlohmann::json;

struct
export_product_data
{
    std::string ProductId;
    std::string Title;
    std::string Type;
    short Amount;
};

struct
export_data
{
    std::string Name;
    std::string ShippingType;
    std::string Address;
    
    std::vector<export_product_data> ExportProducts;
};

std::vector<std::string>
ListDirectoryContents(const char *DirectoryPath)
{
    std::vector<std::string> ExportFiles = {};
    
#ifdef WIN32
    WIN32_FIND_DATA File;
    HANDLE FileHandle;
    
    char Path[MAX_DIRECTORY_PATH_LENGTH];
    
    sprintf(Path, "%s\\*.json", DirectoryPath);
    
    if((FileHandle = FindFirstFile(Path, &File)) == INVALID_HANDLE_VALUE)
    {
        printf("Path not found [%s]\n", DirectoryPath);
        return ExportFiles;
    }
    
    do
    {
        if(strcmp(File.cFileName, ".") != 0 &&
           strcmp(File.cFileName, "..") != 0)
        {
            sprintf(Path, "%s\\%s", DirectoryPath, File.cFileName);
            
            if(File.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
            {
            }
            else
            {
                ExportFiles.push_back(Path);
            }
        }
    } while(FindNextFile(FileHandle, &File));
    
    FindClose(FileHandle);
    
#elif UNIX
    DIR *d;
    struct dirent *dir;
    char Path[MAX_DIRECTORY_PATH_LENGTH] = DirectoryPath;
    d = opendir(Path);
    char full_path[MAX_DIRECTORY_PATH_LENGTH];
    if(d)
    {
        while((dir = readdir(d)) != NULL)
        {
            if(dir->d_type == DT_REG)
            {
                full_path[0] = '\0';
                strcat(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, dir->d_name);
                printf("%s\n", full_apth);
            }
        }
        closedir(d);
    }
#endif
    
    return ExportFiles;
}

export_data
GetExport(std::string& FileName)
{
    std::ifstream ExportFile(FileName);
    json ExportJson = {};
    export_data ExportData = {};
    
    if(ExportFile.is_open())
    {
        ExportJson = json::parse(ExportFile);
        
        ExportData.Name = ExportJson["Pluklist"]["Name"].get<std::string>();
        ExportData.ShippingType = ExportJson["Pluklist"]["ShippingType"].get<std::string>();
        ExportData.Address = ExportJson["Pluklist"]["Address"].get<std::string>();
        
#if 0
        std::cout << "Navn - " << ExportData.Name << std::endl;
        std::cout << "Forsendelsestype - " << ExportData.ShippingType << std::endl;
        std::cout << "Addresse - " << ExportData.Address << std::endl;
#endif
        
        for(auto JsonIterator = ExportJson["Pluklist"]["Lines"]["Item"].begin(); JsonIterator != ExportJson["Pluklist"]["Lines"]["Item"].end(); ++JsonIterator)
        {
            export_product_data ExportProduct = {};
            ExportProduct.ProductId = (*JsonIterator)["ProductID"].get<std::string>();
            ExportProduct.Title = (*JsonIterator)["Title"].get<std::string>();
            ExportProduct.Type = (*JsonIterator)["Type"].get<std::string>();
            ExportProduct.Amount = (*JsonIterator)["Amount"].get<int>();
            
            ExportData.ExportProducts.push_back(ExportProduct);
#if 0
            std::cout << "Product: " << ExportProduct.ProductId << std::endl;
            std::cout << "Title: " << ExportProduct.Title << std::endl;
            std::cout << "Type: " << ExportProduct.Type << std::endl;
            std::cout << "Amount: " << ExportProduct.Amount << std::endl;
#endif
        }
    }
    
    return ExportData;
}

bool
DeleteExport(std::string& FileName)
{
    if(!remove(FileName.c_str()))
    {
        return false;
    }
    
    return true;
}

void
OutputConsoleInformation(std::vector<std::string> ExportFiles, export_data ExportData, int SelectedExport)
{
    printf("Plukliste %i af %i\n\n", SelectedExport+1, (int)ExportFiles.size());
    
    printf("file: %s\n\n", ExportFiles.at(SelectedExport).c_str());
    
    std::cout << "Navn: \t\t" << ExportData.Name << std::endl;
    std::cout << "Forsendelse: \t" << ExportData.ShippingType << std::endl;
    std::cout << "Addresse: \t" << ExportData.Address << std::endl << std::endl;
    
    std::cout << "Antal\tType\t\tProduktnr.\t\tNavn" << std::endl;
    for(int ExportProductIndex = 0;
        ExportProductIndex < (int)ExportData.ExportProducts.size();
        ++ExportProductIndex)
    {
        std::cout << ExportData.ExportProducts.at(ExportProductIndex).Amount << "\t"
            << ExportData.ExportProducts.at(ExportProductIndex).Type.c_str() << "\t\t"
            << ExportData.ExportProducts.at(ExportProductIndex).ProductId.c_str() << "\t\t"
            << ExportData.ExportProducts.at(ExportProductIndex).Title.c_str() << "\t\t"
            << std::endl;
    }
    
    printf("\n[O]ptions:\n[Q]uit\n[D]elete export\n[P]revious export\n[N]ext export\n[R]eload exports\n");
}

int
main()
{
    std::vector<std::string> ExportFiles = ListDirectoryContents("exports");
    
    int SelectedExport = 0;
    export_data ExportData = GetExport(ExportFiles.at(SelectedExport));
    
    bool ApplicationIsRunning = true;
    
    OutputConsoleInformation(ExportFiles, ExportData, SelectedExport);
    
    while(ApplicationIsRunning)
    {
        ExportFiles = ListDirectoryContents("exports");
        
        if(SelectedExport >= ExportFiles.size())
            SelectedExport = ExportFiles.size() - 1;
        
        export_data ExportData = GetExport(ExportFiles.at(SelectedExport));
        
        OutputConsoleInformation(ExportFiles, ExportData, SelectedExport);
        
        char input = _getch();
        while(input != 'q' &&
              input != 'd' &&
              input != 'p' &&
              input != 'n' &&
              input != 'r')
        {
            input = _getch();
        }
        
        switch(input)
        {
            case 'q':
            case 'Q':
            {
                ApplicationIsRunning = false;
            } break;
            
            case 'd':
            case 'D':
            {
                DeleteExport(ExportFiles.at(SelectedExport));
            } break;
            
            case 'p':
            case 'P':
            {
                SelectedExport -= 1;
            } break;
            
            case 'n':
            case 'N':
            {
                SelectedExport += 1;
                if(SelectedExport >= ExportFiles.size())
                    SelectedExport = 0;
            } break;
        }
    }
    
    return 0;
}