/* date = February 16th 2023 10:09 am */

#ifndef EXPORT_H
#define EXPORT_H

#include <fstream>

#ifdef WIN32
#include <windows.h> //For Windows Directory manipulation
#elif UNIX
#include <limits.h> //Linux MAX_PATH
#include <dirent.h> //Linux Directory manipulation
#endif

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define MAX_DIRECTORY_PATH_LENGTH MAX_PATH //Define macro with different name, due to the fact that MAX_PATH is ambiguous

typedef unsigned char uint8;

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
ListDirectoryContents(const char *DirectoryPath);

export_data
GetExportDataJson(std::ifstream& File);

export_data
GetExportDataCSV(std::ifstream& File);

export_data
GetExportData(std::string& FileName);

bool DeleteExport(std::string& FileName);

std::string
GetExportProductsInHTML(export_data ExportData);

#endif //EXPORT_H
