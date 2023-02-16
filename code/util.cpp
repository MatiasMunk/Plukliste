#include "util.h"

std::vector<std::string>
Explode(char delimiter, const std::string& str)
{
    std::size_t lastpos = 0;
    std::size_t pos = 0;
    std::vector<std::string> pieces;
    
    for (pos = str.find_first_of(delimiter); pos != std::string::npos; )
    {
        pieces.emplace_back(str.substr(lastpos, pos - lastpos));
        lastpos = pos + 1;
        pos = str.find_first_of(delimiter, pos + 1);
    }
    pieces.emplace_back(str.substr(lastpos));
    
    return pieces;
}

void
FindAndReplace(std::string& SourceString, std::string ReplaceString, std::string ReplaceWith)
{
    std::size_t pos = SourceString.find(ReplaceString);
    if(pos != std::string::npos)
    {
        SourceString.replace(pos, std::string(ReplaceString).length(), ReplaceWith);
    }
}

std::string
ToLower(std::string String)
{
    std::transform(String.begin(), String.end(), String.begin(), ::tolower);
    
    return String;
}