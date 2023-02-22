#include <conio.h>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "database.h"
#include "export.h"
#include "util.h"

void
OutputConsoleInformation(std::vector<std::string> ExportFiles, export_data ExportData, int SelectedExport,
                         Database& db)
{
    printf("Plukliste %i af %i\n\n", SelectedExport+1, (int)ExportFiles.size());
    
    printf("file: %s\n\n", ExportFiles.at(SelectedExport).c_str());
    
    std::cout << "Navn: \t\t" << ExportData.Name << std::endl;
    std::cout << "Forsendelse: \t" << ExportData.ShippingType << std::endl;
    std::cout << "Addresse: \t" << ExportData.Address << std::endl << std::endl;
    
    
    std::cout << std::setw(9) << std::left << "Antal"
        << std::setw(8) << std::left << "Type"
        << std::setw(25) << std::left << "Produktnr."
        << std::setw(30) << std::left << "Navn"
        << std::setw(9) << std::left << "Lager"
        << std::endl;
    
    for(int ExportProductIndex = 0;
        ExportProductIndex < (int)ExportData.ExportProducts.size();
        ++ExportProductIndex)
    {
        if(IsActualProduct(ExportData.ExportProducts.at(ExportProductIndex)))
        {
            int Stock = 0;
            std::string DBQuery = "SELECT `stock` FROM `products` WHERE `product_id` = \"" + std::string(ExportData.ExportProducts.at(ExportProductIndex).ProductId.c_str()) + "\";";
            
            Database_Result res = db.Query(DBQuery.c_str());
            MYSQL_ROW row;
            unsigned int num_fields = mysql_num_fields(res.Result);
            unsigned int i;
            while((row = mysql_fetch_row(res.Result)))
            {
                unsigned long *lengths;
                lengths = mysql_fetch_lengths(res.Result);
                for(i = 0; i < num_fields; i++)
                {
                    Stock = row[i] ? std::atoi(row[i]) : 0;
                }
            }
            
            std::cout << std::setw(9) << std::left << ExportData.ExportProducts.at(ExportProductIndex).Amount
                << std::setw(8) << std::left << ExportData.ExportProducts.at(ExportProductIndex).Type.c_str()
                << std::setw(25) << std::left << ExportData.ExportProducts.at(ExportProductIndex).ProductId.c_str()
                << std::setw(30) << std::left << ExportData.ExportProducts.at(ExportProductIndex).Title.c_str()
                << std::setw(9) << std::left << std::to_string(Stock)
                << std::endl;
        }
    }
    
    printf("\n[O]ptions:\n[Q]uit\n[D]elete export\n[B]ack\n[N]ext\n[R]eload exports\n[P]rint\n");
}

#define Upgrade 1
#define Termination 2
#define Welcome 3
void
Print(uint8 PrintType, export_data ExportData)
{
    char File[20];
    std::string PrintFilePrefix;
    
    switch(PrintType)
    {
        case Upgrade:
        {
            PrintFilePrefix = "Upgrade-";
            sprintf(File, "PRINT-OPGRADE.html");
        } break;
        
        case Termination:
        {
            PrintFilePrefix = "Termination-";
            sprintf(File, "PRINT-OPSIGELSE.html");
        } break;
        
        case Welcome:
        {
            PrintFilePrefix = "Welcome-";
            sprintf(File, "PRINT-WELCOME.html");
        } break;
    }
    
    std::ifstream TemplateFile("templates/" + std::string(File));
    if(TemplateFile.is_open())
    {
        std::stringstream buffer;
        buffer << TemplateFile.rdbuf();
        
        std::string temp_file_contents = buffer.str();
        
        FindAndReplace(temp_file_contents, "[Adresse]", ExportData.Address);
        FindAndReplace(temp_file_contents, "[Name]", ExportData.Name);
        FindAndReplace(temp_file_contents, "[Plukliste]", GetExportProductsInHTML(ExportData));
        
        std::ofstream PrintFile("udskrift/" + PrintFilePrefix + ExportData.Name + ".html");
        if(PrintFile.is_open())
        {
            PrintFile << temp_file_contents;
        }
        PrintFile.close();
    }
    TemplateFile.close();
}

int
main()
{
    Database db;
    
    if(!db.Connect("localhost", 0, "root", "", "exports"))
    {
        std::exit(1);
    }
    
    std::vector<std::string> ExportFiles;
    export_data ExportData;
    int SelectedExport = 0;
    
    bool ApplicationIsRunning = true;
    
    while(ApplicationIsRunning)
    {
#ifdef WIN32
        std::system("cls");
#elif LINUX
        clrscr();
#endif
        ExportFiles = ListDirectoryContents("exports");
        
        if(SelectedExport >= ExportFiles.size())
            SelectedExport = ExportFiles.size() - 1;
        
        if(ExportFiles.size() > 0)
        {
            ExportData = GetExportData(ExportFiles.at(SelectedExport));
            
            OutputConsoleInformation(ExportFiles, ExportData, SelectedExport, db);
        }
        
        char input = _getch();
        while(input != 'q' &&
              input != 'd' &&
              input != 'b' &&
              input != 'n' &&
              input != 'p' &&
              input != 'r')
        {
            input = _getch();
        }
        
        switch(input)
        {
            case 'q':
            {
                ApplicationIsRunning = false;
            } break;
            
            case 'd':
            {
                if(ExportFiles.size() > 0)
                {
                    DeleteExport(db, ExportFiles.at(SelectedExport));
                }
            } break;
            
            case 'b':
            {
                SelectedExport -= 1;
            } break;
            
            case 'n':
            {
                SelectedExport += 1;
                if(SelectedExport >= ExportFiles.size())
                    SelectedExport = 0;
            } break;
            
            case 'p':
            {
#ifdef WIN32
                std::system("cls");
#elif LINUX
                clrscr();
#endif
                printf("[U]pgrade\n[T]erminate\n[W]elcome");
                input = _getch();
                while(input != 'u' &&
                      input != 't' &&
                      input != 'w')
                {
                    input = _getch();
                }
                
                switch(input)
                {
                    case 'u':
                    {
                        Print(Upgrade, ExportData);
                    } break;
                    case 't':
                    {
                        Print(Termination, ExportData);
                    } break;
                    case 'w':
                    {
                        Print(Welcome, ExportData);
                    } break;
                }
            } break;
        }
    }
    
    return 0;
}