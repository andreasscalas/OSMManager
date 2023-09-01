#ifndef OSM_RELATION_H
#define OSM_RELATION_H

#include "node.h"
#include "way.h"
#include "object.h"

namespace OpenStreetMap
{
    class Relation : public Object
    {
    public:
        Relation();

        std::string getId() const;
        void setId(const std::string &value);

        const std::map<Node *, std::string> &getNodes() const;
        void setNodes(const std::map<Node *, std::string> &newNodes);
        bool addNode(const std::pair<Node*, std::string> node);
        bool removeNode(Node*);
        bool removeNode(std::string osmid);
        bool containsNode(Node * n) const;

        const std::map<Way *, std::string> &getWays() const;
        void setWays(const std::map<Way *, std::string> &newWays);
        bool addWay(const std::pair<Way*, std::string> way);
        bool removeWay(Way*);
        bool removeWay(std::string osmid);
        bool containsWay(Way * w) const;

        const std::map<Relation *, std::string> &getRelations() const;
        void setRelations(const std::map<Relation *, std::string> &newRelations);
        bool addRelation(const std::pair<Relation*, std::string> relation);
        bool removeRelation(Relation*);
        bool removeRelation(std::string osmid);
        bool containsRelation(Relation* r);

        virtual void print(std::ostream &stream) override;
        virtual std::string toXML() override;

    private:
        std::map<Node*, std::string > nodes;
        std::map<Way*, std::string> ways;
        std::map<Relation*, std::string> relations;
    };

}
#endif // OSM_RELATION_H
