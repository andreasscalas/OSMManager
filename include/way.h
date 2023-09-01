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
        ~Way();
        bool removeNode(std::string id);
        const std::vector<Node *> &getNodes() const;
        void setNodes(const std::vector<Node *> &newNodes);
        void addNode(Node *);
        bool containsNode(const Node*) const;
        bool fixRepeatedNodes();

        virtual void print(std::ostream &stream) override;
        virtual std::string toXML() override;

    private:
        std::vector<Node*> nodes;

    };
}
#endif // OSM_WAY_H
