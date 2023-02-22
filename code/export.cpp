#include "export.h"
#include "util.h"

std::vector<std::string>
ListDirectoryContents(const char *DirectoryPath)
{
    std::vector<std::string> ExportFiles = {};
    
#ifdef WIN32
    WIN32_FIND_DATA File;
    HANDLE FileHandle;
    
    char Path[MAX_DIRECTORY_PATH_LENGTH];
    
    sprintf(Path, "%s\\*.*", DirectoryPath);
    
    if((FileHandle = FindFirstFile(Path, &File)) == INVALID_HANDLE_VALUE)
    {
        printf("Path is invalid, or no exports were found\n");
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
GetExportDataJson(std::ifstream& File)
{
    json ExportJson = {};
    export_data ExportData = {};
    
    ExportJson = json::parse(File);
    
    ExportData.Name = ExportJson["Pluklist"]["Name"].get<std::string>();
    ExportData.ShippingType = ExportJson["Pluklist"]["ShippingType"].get<std::string>();
    ExportData.Address = ExportJson["Pluklist"]["Address"].get<std::string>();
    
#if 0
    std::cout << "Navn - " << ExportData.Name << std::endl;
    std::cout << "Forsendelsestype - " << ExportData.ShippingType << std::endl;
    std::cout << "Addresse - " << ExportData.Address << std::endl;
#endif
    
    for(auto JsonIterator = ExportJson["Pluklist"]["Lines"]["Item"].begin();
        JsonIterator != ExportJson["Pluklist"]["Lines"]["Item"].end();
        ++JsonIterator)
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
    
    return ExportData;
}

export_data
GetExportDataCSV(std::ifstream& File)
{
    export_data ExportData = {};
    ExportData.Name = "";
    ExportData.ShippingType = "Pickup";
    ExportData.Address = "On location";
    
    while(!File.eof())
    {
        bool FirstLine = true;
        for(std::string Line; std::getline(File, Line);)
        {
            if(FirstLine == true)
            {
                FirstLine = false;
                continue;
            }
            
            export_product_data ExportProduct = {};
            std::vector<std::string> ProductData = Explode(';', Line);
            ExportProduct.ProductId = ProductData.at(0);
            ExportProduct.Type = ProductData.at(1);
            ExportProduct.Title = ProductData.at(2);
            ExportProduct.Amount = std::stoi(ProductData.at(3));
            ExportData.ExportProducts.push_back(ExportProduct);
        }
    }
    
    return ExportData;
}

bool
IsActualProduct(export_product_data ExportProduct)
{
    if(ExportProduct.ProductId.find("PRINT") != std::string::npos ||
       ExportProduct.ProductId.find("LABEL") != std::string::npos)
    {
        return false;
    }
    else
    {
        return true;
    }
}

export_data
GetExportData(std::string& FileName)
{
    std::ifstream ExportFile(FileName);
    export_data ExportData = {};
    
    if(ExportFile.is_open())
    {
        if(ToLower(FileName).find(".json") != std::string::npos)
        {
            ExportData = GetExportDataJson(ExportFile);
        }
        else if(ToLower(FileName).find(".csv") != std::string::npos)
        {
            ExportData = GetExportDataCSV(ExportFile);
        }
    }
    
    return ExportData;
}

bool
DeleteExport(Database& db, std::string& FileName)
{
    export_data ExportData = GetExportData(FileName);
    
    if(remove(FileName.c_str()) != 0)
    {
        return false;
    }
    
    for(auto Product : ExportData.ExportProducts)
    {
        if(IsActualProduct(Product))
        {
            std::string DBQuery = "UPDATE `products` SET stock = stock - " + std::to_string(Product.Amount) + " WHERE `product_id` = '" +
                std::string(Product.ProductId.c_str()) + "';";
            
            Database_Result res = db.Query(DBQuery.c_str());
            std::cout << res.Result << std::endl;
        }
    }
    
    return true;
}

std::string
GetExportProductsInHTML(export_data ExportData)
{
    std::string ExportProducts;
    
    ExportProducts.append("<table>");
    ExportProducts.append("<tr>");
    ExportProducts.append("<th>Antal</th>");
    ExportProducts.append("<th>Produktnr.</th>");
    ExportProducts.append("<th>Navn</th>");
    ExportProducts.append("</tr>");
    
    for(int ExportProductIndex = 0;
        ExportProductIndex < (int)ExportData.ExportProducts.size();
        ++ExportProductIndex)
    {
        ExportProducts.append("<tr>");
        ExportProducts.append("<td>" + std::to_string(ExportData.ExportProducts.at(ExportProductIndex).Amount) + "</td>");
        ExportProducts.append("<td>" + ExportData.ExportProducts.at(ExportProductIndex).ProductId + "</td>");
        ExportProducts.append("<td>" + ExportData.ExportProducts.at(ExportProductIndex).Title + "</td>");
        ExportProducts.append("</tr>");
    }
    
    ExportProducts.append("</table>");
    
    return ExportProducts;
}