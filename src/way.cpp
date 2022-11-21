#include "way.h"
#include <sstream>
#include <regex>
#include <utils.h>

using namespace OpenStreetMap;

Way::Way()
{

}

std::string Way::getId() const
{
    return id;
}

void Way::setId(const std::string &value)
{
    id = value;
}

std::string Way::getUserName() const
{
    return user_name;
}

void Way::setUserName(const std::string &value)
{
    user_name = value;
}

std::string Way::getUserId() const
{
    return user_id;
}

void Way::setUserId(const std::string &value)
{
    user_id = value;
}

bool Way::getIsVisible() const
{
    return is_visible;
}

void Way::setIsVisible(bool value)
{
    is_visible = value;
}

std::string Way::getVersion() const
{
    return version;
}

void Way::setVersion(const std::string &value)
{
    version = value;
}

std::string Way::getChangeset() const
{
    return changeset;
}

void Way::setChangeset(const std::string &value)
{
    changeset = value;
}


const std::map<std::string, std::string> &Way::getTags() const
{
    return tags;
}

void Way::setTags(const std::map<std::string, std::string> &newTags)
{
    tags = newTags;
}


bool Way::checkTag(std::pair<std::string, std::string> tag)
{
    auto iterator = tags.find(tag.first);
    if(iterator != tags.end())
        return tag.second.compare("") == 0 || tag.second.compare(iterator->second) == 0;

    return false;
}

std::string Way::getTimestamp() const
{
    return timestamp;
}

void Way::setTimestamp(const std::string &value)
{
    timestamp = value;
}

const std::vector<Node *> &Way::getNodes() const
{
    return nodes;
}

void Way::setNodes(const std::vector<Node *> &newNodes)
{
    nodes = newNodes;
}

bool Way::removeNode(std::string id)
{
    for(unsigned int i = 0; i < nodes.size(); i++)
        if(nodes.at(i)->getId().compare(id) == 0)
        {
            nodes.erase(nodes.begin() + i);
            return true;
        }
    return false;
}

std::string Way::toXML()
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
