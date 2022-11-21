#ifndef OSMUTILS_H
#define OSMUTILS_H
#include <string>
#include <map>
#include <fstream>
#include <regex>

namespace OpenStreetMap {


    inline void checkStringContainsSpecialCharacters(std::string &s)
    {
        s = std::regex_replace(s, std::regex("&"), "&amp;");
        s = std::regex_replace(s, std::regex("\""), "&quot;");

    }
}
#endif // OSMUTILS_H
