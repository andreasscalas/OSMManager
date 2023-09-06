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
        virtual ~Relation() override;

        std::string getId() const;
        void setId(const std::string &value);

        const std::map<Node *, std::string> &getNodes() const;
        void setNodes(const std::map<Node *, std::string> &newNodes);
        bool addNode(const std::pair<Node*, std::string> node);
        bool removeNode(const Node*);
        bool removeNode(const std::string osmid);
        bool containsNode(const Node * n) const;

        const std::map<Way *, std::string> &getWays() const;
        void setWays(const std::map<Way *, std::string> &newWays);
        bool addWay(const std::pair<Way*, std::string> way);
        bool removeWay(const Way*);
        bool removeWay(const std::string& osmid);
        bool containsWay(const Way * w) const;

        const std::map<Relation *, std::string> &getRelations() const;
        void setRelations(const std::map<Relation *, std::string> &newRelations);
        bool addRelation(const std::pair<Relation*, std::string> relation);
        bool removeRelation(Relation*);
        bool removeRelation(std::string osmid);
        bool containsRelation(const Relation* r) const;

        virtual void print(std::ostream &stream) const override;
        virtual std::string toXML() const override;

    private:
        std::map<Node*, std::string > nodes;
        std::map<Way*, std::string> ways;
        std::map<Relation*, std::string> relations;
    };

}
#endif // OSM_RELATION_H
