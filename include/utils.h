#ifndef OSM_UTILS_H
#define OSM_UTILS_H
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
#endif // OSM_UTILS_H
