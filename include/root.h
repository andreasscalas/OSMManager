#ifndef ROOT_H
#define ROOT_H

#include <string>
#include <node.h>
#include <way.h>
#include <relation.h>
#include <types.h>
namespace OpenStreetMap
{
    class Root
    {
    public:
        Root();
        ~Root();
        int load(std::string filename);
        int save(std::string filename);
    private:
        std::vector<std::pair<std::string, OpenStreetMap::Node*> > nodes;
        std::vector<std::pair<std::string, OpenStreetMap::Way* > > ways;
        std::vector<std::pair<std::string, OpenStreetMap::Relation* > >relations;
        std::string version;
        std::string generator;
        std::string copyright;
        std::string attribution;
        std::string license;
        Point min, max;
    };
}

#endif // ROOT_H
