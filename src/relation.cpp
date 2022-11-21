#include "relation.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <utils.h>
using namespace OpenStreetMap;

Relation::Relation()
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

std::string Relation::getUserName() const
{
    return user_name;
}

void Relation::setUserName(const std::string &value)
{
    user_name = value;
}

std::string Relation::getUserId() const
{
    return user_id;
}

void Relation::setUserId(const std::string &value)
{
    user_id = value;
}

bool Relation::getIsVisible() const
{
    return is_visible;
}

void Relation::setIsVisible(bool value)
{
    is_visible = value;
}

std::string Relation::getVersion() const
{
    return version;
}

void Relation::setVersion(const std::string &value)
{
    version = value;
}

std::string Relation::getChangeset() const
{
    return changeset;
}

void Relation::setChangeset(const std::string &value)
{
    changeset = value;
}


bool Relation::checkTag(std::pair<std::string, std::string> tag)
{
    auto iterator = tags.find(tag.first);
    if(iterator != tags.end())
        return tag.second.compare("") == 0 || tag.second.compare(iterator->second) == 0;

    return false;
}

std::string Relation::getTimestamp() const
{
    return timestamp;
}

void Relation::setTimestamp(const std::string &value)
{
    timestamp = value;
}

const std::map<std::string, std::string> &Relation::getTags() const
{
    return tags;
}

void Relation::setTags(const std::map<std::string, std::string> &newTags)
{
    tags = newTags;
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

bool Relation::removeNode(Node* node)
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

bool Relation::removeWay(Way* relation)
{
    return removeWay(relation->getId());
}

bool Relation::removeWay(std::string osmid)
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

std::string Relation::toXML()
{
    std::stringstream ss;
    ss << "<relation id=\"" << id << "\" visible=\"";
    if(is_visible)
        ss << "true";
    ss << "\" version=\"" << version << "\" changeset=\"" <<  changeset << "\" timestamp=\"" << timestamp;
    ss << "\" user=\"" << user_name << "\" uid=\"" << user_id << "\">" << std::endl;

    for(auto node : nodes)
        if(node.first != nullptr)
            ss << "\t<member type=\"node\" ref=\"" << node.first->getId() << "\" role=\"" << node.second << "\" />" << std::endl;
    for(auto way : ways)
        if(way.first != nullptr)
            ss << "\t<member type=\"way\" ref=\"" << way.first->getId() << "\" role=\"" << way.second << "\" />" << std::endl;
    for(auto relation : relations)
        if(relation.first != nullptr)
            ss << "\t<member type=\"relation\" ref=\"" << relation.first->getId() << "\" role=\"" << relation.second << "\" />" << std::endl;
    for(auto tag : tags)
    {
        checkStringContainsSpecialCharacters(tag.second);
        ss << "\t<tag k=\"" << tag.first << "\" v=\"" << tag.second << "\" />" << std::endl;
    }
    ss << "</relation>" << std::endl;
    return ss.str();
}
