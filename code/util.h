/* date = February 16th 2023 10:10 am */

#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string>
Explode(char delimiter, const std::string& str);

void
FindAndReplace(std::string& SourceString, std::string ReplaceString, std::string ReplaceWith);

std::string
ToLower(std::string String);

#endif //UTIL_H
