#include "way.h"
#include "utils.h"
#include <sstream>
#include <regex>

using namespace OpenStreetMap;

Way::Way()
{

}

Way::~Way()
{

}

const std::vector<Node *> &Way::getNodes() const
{
    return nodes;
}

void Way::setNodes(const std::vector<Node *> &newNodes)
{
    nodes = newNodes;
}

void Way::addNode(Node * n)
{
    nodes.push_back(n);
}

bool Way::containsNode(const Node * n) const
{
    return std::find(nodes.begin(), nodes.end(), n) != nodes.end();
}

bool Way::fixRepeatedNodes()
{
    bool fixed = false;
    for(uint i = 0; i < nodes.size(); i++)
    {
        auto tmp = nodes.at(i);
        std::vector<Node*>::iterator it = nodes.end();
        do {
            if(it != nodes.end())
            {
                removeNode((*it)->getId());
                fixed = true;
            }
            it = std::find_if(nodes.begin() + i + 1, nodes.end(), [tmp](Node* n){
                return *tmp->getCoordinates() == *n->getCoordinates();
            });

        } while( it != nodes.end());
    }

    return fixed;
}

bool Way::removeNode(const std::string& rid)
{
    auto it = std::find_if(nodes.begin(), nodes.end(), [rid](Node* n){ return n->getId().compare(rid) == 0; });
    if(it != nodes.end())
    {
        nodes.erase(it);
        return true;
    }
    return false;
}

void Way::print(std::ostream &stream) const
{

    Object::print(stream);
    stream << "Nodes:" << std::endl;
    stream << "[" << std::endl;
    for(auto n : nodes)
        stream << "\t" << n->getId() << std::endl;
    stream << "]" << std::endl;
}

std::string Way::toXML() const
{
    std::stringstream ss;
    ss << "<way id=\"" << id << "\" visible=\"";
    if(is_visible)
        ss << "true";
    ss << "\" version=\"" << version << "\" changeset=\"" <<  changeset << "\" timestamp=\"" << timestamp;
    ss << "\" user=\"" << user_name << "\" uid=\"" << user_id << "\">" << std::endl;

    for(auto node : nodes)
        ss << "\t<nd ref=\"" << node->getId() << "\" />" << std::endl;
    for(auto tag : tags)
    {
        checkStringContainsSpecialCharacters(tag.second);
        ss << "\t<tag k=\"" << tag.first << "\" v=\"" << tag.second << "\" />" << std::endl;
    }
    ss << "</way>" << std::endl;
    return ss.str();
}
