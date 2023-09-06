#ifndef OSM_WAY_H
#define OSM_WAY_H

#include "node.h"
#include "object.h"
#include <memory>
#include <vector>

namespace OpenStreetMap
{
    class Way : public Object
    {
    public:
        Way();
        virtual ~Way() override ;
        bool removeNode(const std::string& id);
        const std::vector<Node *> &getNodes() const;
        void setNodes(const std::vector<Node *> &newNodes);
        void addNode(Node *);
        bool containsNode(const Node*) const;
        bool fixRepeatedNodes();

        virtual void print(std::ostream &stream) const override;
        virtual std::string toXML() const override;

    private:
        std::vector<Node*> nodes;

    };
}
#endif // OSM_WAY_H
