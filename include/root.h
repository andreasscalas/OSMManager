#ifndef OSM_ROOT_H
#define OSM_ROOT_H

#include <string>
#include <node.h>
#include "way.h"
#include "relation.h"
#include "types.h"
namespace OpenStreetMap
{
    class Root
    {
    public:
        Root();
        ~Root();
        /**
         * @brief load method parsing an OSM formatted XML file (.osm)
         * @param filename the filename (path + actual name) of the file
         * @return error code, equals 0 if no error is detected.
         */
        int load(const std::string& filename);
        int save(const std::string& filename);

        const std::map<std::string, Node *> &getNodes() const;
        const std::vector<Node *> getNodes(const std::string &key, const std::string &value = "") const;
        Node* getNode(const std::string&) const;
        void addNode(Node *);
        std::map<std::string, Node*>::iterator removeNode(const std::string &id);

        const std::map<std::string, Way *> &getWays() const;
        std::vector<Way *> getWays(const Node*) const;
        Way* getWay(const std::string&) const;
        void addWay(Way *);
        std::map<std::string, Way*>::iterator removeWay(const std::string &id);
        std::vector<Way *> getWays(const std::string &key, const std::string &value = "") const;

        const std::map<std::string, Relation *> &getRelations() const;
        std::vector<Relation *> getRelations(const Node *n) const;
        std::vector<Relation *> getRelations(const Way *w) const;
        std::vector<Relation *> getRelations(const Relation *r) const;
        std::vector<Relation *> getRelations(const std::string& key, const std::string& value = "") const;
        Relation* getRelation(const std::string&) const;

        void addRelation(Relation *);
        std::map<std::string, Relation*>::iterator removeRelation(const std::string&);

        const std::string &getVersion() const;

        const std::string &getGenerator() const;

        const std::string &getCopyright() const;

        const std::string &getAttribution() const;

        const std::string &getLicense() const;

        Point getMin() const;

        Point getMax() const;

        void setVersion(const std::string &newVersion);

        void setGenerator(const std::string &newGenerator);

        void setCopyright(const std::string &newCopyright);

        void setAttribution(const std::string &newAttribution);

        void setLicense(const std::string &newLicense);

        void setMin(Point newMin);

        void setMax(Point newMax);

    private:
        std::map<std::string, Node*> nodes;
        std::map<std::string, Way*> ways;
        std::map<std::string, Relation*> relations;
        std::string version;
        std::string generator;
        std::string copyright;
        std::string attribution;
        std::string license;
        Point min;
        Point max;
    };
}

#endif // OSM_ROOT_H
