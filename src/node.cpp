#include "node.h"
#include <iostream>
#include <sstream>
#include <tinyxml2.h>
#include <utils.h>
#include <algorithm>
using namespace OpenStreetMap;
Node::Node()
{
    coordinates = new Point();
}

Node::~Node()
{
    delete coordinates;
}


std::string Node::getTimestamp() const
{
    return timestamp;
}

void Node::setTimestamp(const std::string &value)
{
    timestamp = value;
}


Point *Node::getCoordinates() const
{
    return coordinates;
}

void Node::setCoordinates(double x, double y)
{
    coordinates->x = x;
    coordinates->y = y;
}

void Node::setCoordinates(Point newCoordinates)
{
    *coordinates = newCoordinates;
}

void Node::setCoordinates(Point *newCoordinates)
{
    delete coordinates;
    coordinates = newCoordinates;
}

const std::map<std::string, std::string> &Node::getTags() const
{
    return tags;
}

void Node::setTags(const std::map<std::string, std::string> &newTags)
{
    tags = newTags;
}

bool Node::checkTag(const std::pair<std::string, std::string> tag) const
{
    auto iterator = tags.find(tag.first);
    if(iterator != tags.end())
        return tag.second.compare("") == 0 || tag.second.compare(iterator->second) == 0;

    return false;
}

void Node::print(std::ostream &stream)
{
    stream << id << std::endl;
    stream << user_name << std::endl;
    stream << version << std::endl;
    stream << changeset << std::endl;
    stream << timestamp << std::endl;
    stream << coordinates->x << coordinates->y << std::endl;
    stream << is_visible << std::endl;
    stream << "Tags: "<< std::endl;
    for(auto t : tags)
        stream << "\tKey: " << t.first << ", value: " << t.second << std::endl;
}

std::string Node::toXML()
{
    std::stringstream ss;
    ss.precision(15);
    ss << "<node id=\"" << id << "\" visible=\"";
    if(is_visible)
        ss << "true";
    ss << "\" version=\"" << version << "\" changeset=\"" <<  changeset << "\" timestamp=\"" << timestamp;
    ss << "\" user=\"" << user_name << "\" uid=\"" << user_id << "\" lat=\"" << coordinates->x << "\" lon=\"" << coordinates->y << "\"";
    if(tags.size() == 0)
        ss << "/>";
    else
    {
        ss << ">" << std::endl;
        for(auto tag : tags)
        {

            checkStringContainsSpecialCharacters(tag.second);

            ss << "\t<tag k=\"" << tag.first << "\" v=\"" << tag.second << "\" />" << std::endl;
        }
        ss << "</node>";

    }
    ss  << std::endl;
    return ss.str();
}

std::string Node::getId() const
{
    return id;
}

void Node::setId(const std::string &value)
{
    id = value;
}

std::string Node::getUserName() const
{
    return user_name;
}

void Node::setUserName(const std::string &value)
{
    user_name = value;
}

std::string Node::getUserId() const
{
    return user_id;
}

void Node::setUserId(const std::string &value)
{
    user_id = value;
}

std::string Node::getVersion() const
{
    return version;
}

void Node::setVersion(const std::string &value)
{
    version = value;
}

std::string Node::getChangeset() const
{
    return changeset;
}

void Node::setChangeset(const std::string &value)
{
    changeset = value;
}

bool Node::isVisible() const
{
    return is_visible;
}

void Node::setVisible(bool value)
{
    is_visible = value;
}
