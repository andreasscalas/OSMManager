#include "relation.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <sstream>
using namespace OpenStreetMap;

Relation::Relation()
{

}

Relation::~Relation()
{

}

std::string Relation::getId() const
{
    return id;
}

void Relation::setId(const std::string &value)
{
    id = value;
}


const std::map<Relation *, std::string> &Relation::getRelations() const
{
    return relations;
}

void Relation::setRelations(const std::map<Relation *, std::string> &newRelations)
{
    relations = newRelations;
}

bool Relation::addRelation(const std::pair<Relation*, std::string> relation)
{
    relations.insert(relation);
    return true;
}

bool Relation::removeRelation(Relation* relation)
{
    auto iterator = relations.find(relation);
    if(iterator != relations.end())
    {
        relations.erase(iterator);
        return true;
    }
    return false;
}

bool Relation::removeRelation(std::string osmid)
{
    auto it = std::find_if(relations.begin(), relations.end(),
                           [osmid](std::pair<Relation*, std::string> r) { return r.first->getId().compare(osmid) == 0;});
    if(it != relations.end())
    {
        relations.erase(it);
        return true;
    }
    return false;
}

bool Relation::containsRelation(const Relation *r) const
{
    bool found = relations.find(const_cast<Relation*>(r)) != relations.end();
    if(!found)
        for(const auto &r_ : relations)
            if(r_.first != nullptr)
                r_.first->containsRelation(r);
    return found;
}

const std::map<Node *, std::string> &Relation::getNodes() const
{
    return nodes;
}

void Relation::setNodes(const std::map<Node *, std::string> &newNodes)
{
    nodes = newNodes;
}

bool Relation::addNode(const std::pair<Node*, std::string> node)
{
    nodes.insert(node);
    return true;
}

bool Relation::removeNode(const Node *node)
{
    return removeNode(node->getId());
}

bool Relation::removeNode(std::string osmid)
{

    auto it = std::find_if(nodes.begin(), nodes.end(),
                           [osmid](std::pair<Node*, std::string> n) { return n.first->getId().compare(osmid) == 0;});
    if(it != nodes.end())
    {
        nodes.erase(it);
        return true;
    }
    return false;
}

bool Relation::containsNode(const Node *n) const
{
    bool found = nodes.find(const_cast<Node*>(n)) != nodes.end();
    if(!found)
        for(const auto& w : ways)
            if(w.first != nullptr)
            {
                found = w.first->containsNode(n);
                if(found)
                    break;
            }
    if(!found)
        for(const auto &r : relations)
            if(r.first != nullptr)
            {
                found = r.first->containsNode(n);
                if(found)
                    break;
            }
    return found;

}

const std::map<Way *, std::string> &Relation::getWays() const
{
    return ways;
}

void Relation::setWays(const std::map<Way *, std::string> &newWays)
{
    ways = newWays;
}

bool Relation::addWay(const std::pair<Way*, std::string> way)
{
    ways.insert(way);
    return true;
}

bool Relation::removeWay(const Way *relation)
{
    return removeWay(relation->getId());
}

bool Relation::removeWay(const std::string &osmid)
{
    auto it = std::find_if(ways.begin(), ways.end(),
                           [osmid](std::pair<Way*, std::string> w) { return w.first->getId().compare(osmid) == 0;});
    if(it != ways.end())
    {
        ways.erase(it);
        return true;
    }
    return false;
}

bool Relation::containsWay(const Way *w) const
{
    bool found = ways.find(const_cast<Way*>(w)) != ways.end();
    if(!found)
        for(const auto& r : relations)
            if(r.first != nullptr){
                found = r.first->containsWay(w);
                if(found)
                    break;
            }
    return found;
}


void Relation::print(std::ostream &stream) const
{
    Object::print(stream);
    stream << "]" << std::endl;
    stream << "Nodes:" << std::endl;
    stream << "[" << std::endl;
    for(const auto &n : nodes)
        stream << "\t" << n.first->getId() << std::endl;
    stream << "]" << std::endl;
    stream << "Ways:" << std::endl;
    stream << "[" << std::endl;
    for(const auto &w : ways)
        stream << "\t" << w.first->getId() << std::endl;
    stream << "]"<< std::endl;
    stream << "Relations:" << std::endl;
    stream << "[" << std::endl;
    for(const auto &r : relations)
        stream << "\t" << r.first->getId() << std::endl;
    stream << "]"<< std::endl;
}

std::string Relation::toXML() const
{
    std::stringstream ss;
    ss << "<relation id=\"" << id << "\" visible=\"";
    if(is_visible)
        ss << "true";
    ss << "\" version=\"" << version << "\" changeset=\"" <<  changeset << "\" timestamp=\"" << timestamp;
    ss << "\" user=\"" << user_name << "\" uid=\"" << user_id << "\">" << std::endl;

    for(const auto &node : nodes)
        if(node.first != nullptr)
            ss << "\t<member type=\"node\" ref=\"" << node.first->getId() << "\" role=\"" << node.second << "\" />" << std::endl;
    for(const auto &way : ways)
        if(way.first != nullptr)
            ss << "\t<member type=\"way\" ref=\"" << way.first->getId() << "\" role=\"" << way.second << "\" />" << std::endl;
    for(const auto &relation : relations)
        if(relation.first != nullptr)
            ss << "\t<member type=\"relation\" ref=\"" << relation.first->getId() << "\" role=\"" << relation.second << "\" />" << std::endl;
    for(const auto &tag : tags)
    {
        std::string tagValueCopy = tag.second;
        checkStringContainsSpecialCharacters(tagValueCopy);
        ss << "\t<tag k=\"" << tag.first << "\" v=\"" << tag.second << "\" />" << std::endl;
    }
    ss << "</relation>" << std::endl;
    return ss.str();
}
