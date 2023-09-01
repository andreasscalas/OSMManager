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
    if(coordinates != nullptr)
        delete coordinates;
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
    *coordinates = *newCoordinates;
}

void Node::print(std::ostream &stream)
{
    Object::print(stream);
    stream << "(" << coordinates->x << "," << coordinates->y << ")" << std::endl;
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

