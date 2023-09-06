#include "object.h"
#include "utils.h"

#include <iostream>
#include <sstream>

using namespace OpenStreetMap;

Object::Object()
{
    user_name = "";
    user_id = "";
    version = "";
    changeset = "";
    timestamp = "";
    setVisible(true);
}

Object::~Object()
{

}

std::string Object::getTimestamp() const
{
    return timestamp;
}

void Object::setTimestamp(const std::string &value)
{
    timestamp = value;
}

const std::map<std::string, std::string> &Object::getTags() const
{
    return tags;
}

void Object::setTags(const std::map<std::string, std::string> &newTags)
{
    tags = newTags;
}

void Object::addTag(const std::pair<std::string, std::string> &newTag)
{
    tags.insert(newTag);
}

bool Object::checkTag(const std::pair<std::string, std::string> &tag) const
{
    auto iterator = tags.find(tag.first);
    if(iterator != tags.end())
        return tag.second.compare("") == 0 || tag.second.compare(iterator->second) == 0;

    return false;
}

void Object::print(std::ostream &stream) const
{
    stream << id << std::endl;
    stream << user_name << std::endl;
    stream << version << std::endl;
    stream << changeset << std::endl;
    stream << timestamp << std::endl;
    stream << is_visible << std::endl;
    stream << "Tags: "<< std::endl;
    for(const auto &t : tags)
        stream << "\tKey: " << t.first << ", value: " << t.second << std::endl;
}

std::string Object::toXML() const
{
    std::stringstream ss;
    ss.precision(15);
    ss << "<node id=\"" << id << "\" visible=\"";
    if(is_visible)
        ss << "true";
    ss << "\" version=\"" << version << "\" changeset=\"" <<  changeset << "\" timestamp=\"" << timestamp;
    ss << "\" user=\"" << user_name << "\" uid=\"" << user_id << "\"";
    if(tags.size() == 0)
        ss << "/>";
    else
    {
        ss << ">" << std::endl;
        for(const auto &tag : tags)
        {

            std::string tagValueCopy = tag.second;
            checkStringContainsSpecialCharacters(tagValueCopy);

            ss << "\t<tag k=\"" << tag.first << "\" v=\"" << tag.second << "\" />" << std::endl;
        }
        ss << "</node>";

    }
    ss  << std::endl;
    return ss.str();
}

std::string Object::getId() const
{
    return id;
}

void Object::setId(const std::string &value)
{
    id = value;
}

std::string Object::getUserName() const
{
    return user_name;
}

void Object::setUserName(const std::string &value)
{
    user_name = value;
}

std::string Object::getUserId() const
{
    return user_id;
}

void Object::setUserId(const std::string &value)
{
    user_id = value;
}

std::string Object::getVersion() const
{
    return version;
}

void Object::setVersion(const std::string &value)
{
    version = value;
}

std::string Object::getChangeset() const
{
    return changeset;
}

void Object::setChangeset(const std::string &value)
{
    changeset = value;
}

bool Object::isVisible() const
{
    return is_visible;
}

void Object::setVisible(bool value)
{
    is_visible = value;
}
