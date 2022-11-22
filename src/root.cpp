#include "root.h"
#include <tinyxml2.h>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace OpenStreetMap;
Root::Root()
{

}

Root::~Root()
{
    for(auto node : nodes)
        delete node.second;
    nodes.clear();
    for(auto way : ways)
        delete way.second;
    ways.clear();
    for(auto relation : relations)
        delete relation.second;
    relations.clear();
}

int Root::load(std::string filename)
{
    if(filename.compare("") == 0)
        return 1;
    tinyxml2::XMLDocument document;
    document.LoadFile(filename.c_str());

    if(!document.Error())
    {
        tinyxml2::XMLElement* osmRoot = document.FirstChildElement();
        auto tmpVersion = osmRoot->Attribute("version");
        if(tmpVersion == nullptr)
            return 2;
        version = tmpVersion;
        auto tmpGenerator = osmRoot->Attribute("generator");
        if(tmpGenerator == nullptr)
            return 3;
        generator = tmpGenerator;
        auto tmpCopyright = osmRoot->Attribute("copyright");
        if(tmpCopyright == nullptr)
            return 4;
        copyright = tmpCopyright;
        auto tmpAttribution =  osmRoot->Attribute("attribution");
        if(tmpAttribution == nullptr)
            return 5;
        attribution = tmpAttribution;
        auto tmpLicense =  osmRoot->Attribute("license");
        if(tmpLicense == nullptr)
            return 6;
        license = tmpLicense;
        tinyxml2::XMLElement* xmlBounds = osmRoot->FirstChildElement("bounds");
        if(xmlBounds == nullptr)
            return 7;
        auto tmpMinLat = xmlBounds->Attribute("minlat");
        if(tmpMinLat == nullptr)
            return 8;
        min.x = std::stod(tmpMinLat);
        auto tmpMinLon = xmlBounds->Attribute("minlon");
        if(tmpMinLon == nullptr)
            return 9;
        min.y = std::stod(tmpMinLon);
        auto tmpMaxLat = xmlBounds->Attribute("maxlat");
        if(tmpMaxLat == nullptr)
            return 10;
        max.x = std::stod(tmpMaxLat);
        auto tmpMaxLon = xmlBounds->Attribute("maxlon");
        if(tmpMaxLon == nullptr)
            return 11;
        max.y = std::stod(tmpMaxLon);
        tinyxml2::XMLElement* xmlNode = osmRoot->FirstChildElement("node");

        while(xmlNode != nullptr){

            Node* node = new Node();
            std::map<std::string, std::string> tags;
            const char* id = xmlNode->Attribute("id");
            if(id == nullptr)
            {
                delete node;
                return -1;
            }
            node->setId(id);

            const char* userName = xmlNode->Attribute("user");
            if(userName == nullptr)
            {
                delete node;
                return -2;
            }
            node->setUserName(userName);
            const char* userId = xmlNode->Attribute("uid");
            if(userId == nullptr)
            {
                delete node;
                return -3;
            }
            node->setUserId(userId);
            const char* latitude = xmlNode->Attribute("lat");
            const char* longitude = xmlNode->Attribute("lon");
            if(latitude == nullptr || longitude == nullptr)
            {
                delete node;
                return -4;
            }


            double lat = strtod(latitude, nullptr), lon = strtod(longitude, nullptr), x, y;
            Point coordinates;
            coordinates.x = lat;
            coordinates.y = lon;
            node->setCoordinates(coordinates);

            const char* isVisible = xmlNode->Attribute("visible");
            if(isVisible == nullptr)
            {
                delete node;
                return -5;
            }
            node->setVisible(strcmp(isVisible, "true") == 0);

            const char* version = xmlNode->Attribute("version");
            if(version == nullptr)
            {
                delete node;
                return -6;
            }
            node->setVersion(version);

            const char* changeset = xmlNode->Attribute("changeset");
            if(changeset == nullptr)
            {
                delete node;
                return -7;
            }
            node->setChangeset(changeset);


            const char* timestamp = xmlNode->Attribute("timestamp");
            if(timestamp == nullptr)
            {
                delete node;
                return -8;
            }
            node->setTimestamp(timestamp);

            tinyxml2::XMLElement* xmlTag = xmlNode->FirstChildElement("tag");
            while(xmlTag != nullptr){
                const char* key = xmlTag->Attribute("k");
                const char* value = xmlTag->Attribute("v");
                if(key == nullptr || value == nullptr)
                {
                    delete node;
                    return -8;
                }

                tags.insert(std::make_pair(key, value));
                xmlTag = xmlTag->NextSiblingElement("tag");
            }

            node->setTags(tags);
            xmlNode = xmlNode->NextSiblingElement("node");

            nodes.insert(std::make_pair(node->getId(), node));
        }

        tinyxml2::XMLElement* xmlWay = osmRoot->FirstChildElement("way");

        while(xmlWay != nullptr){

            Way* way = new Way();
            std::map<std::string, std::string> tags;
            std::vector<Node*> connected;
            const char* id = xmlWay->Attribute("id");
            if(id == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                delete way;
                return -9;
            }
            way->setId(id);
            const char* userName = xmlWay->Attribute("user");
            if(userName == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                delete way;
                return -10;
            }
            way->setUserName(userName);
            const char* userId = xmlWay->Attribute("uid");
            if(userId == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                delete way;
                return -11;
            }
            way->setUserId(userId);

            const char* isVisible = xmlWay->Attribute("visible");
            if(isVisible == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                delete way;
                return -12;
            }
            way->setIsVisible(strcmp(isVisible, "true") == 0);

            const char* version = xmlWay->Attribute("version");
            if(version == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                delete way;
                return -13;
            }
            way->setVersion(version);

            const char* changeset = xmlWay->Attribute("changeset");
            if(changeset == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                delete way;
                return -14;
            }
            way->setChangeset(changeset);

            const char* timestamp = xmlWay->Attribute("timestamp");
            if(timestamp == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                delete way;
                return -15;
            }
            way->setTimestamp(timestamp);

            tinyxml2::XMLElement* xmlConnected = xmlWay->FirstChildElement("nd");
            while(xmlConnected != nullptr){
                const char* ref = xmlConnected->Attribute("ref");
                if(ref == nullptr)
                {
                    for(auto node : nodes)
                        delete node.second;
                    delete way;
                    return -16;
                }

                if(nodes.find(ref) != nodes.end())
                {
                    connected.push_back(nodes[ref]);
                }
                xmlConnected = xmlConnected->NextSiblingElement("nd");
            }

            way->setNodes(connected);
            tinyxml2::XMLElement* xmlTag = xmlWay->FirstChildElement("tag");
            while(xmlTag != nullptr){
                const char* key = xmlTag->Attribute("k");
                const char* value = xmlTag->Attribute("v");
                if(key == nullptr || value == nullptr)
                {
                    for(auto node : nodes)
                        delete node.second;
                    delete way;
                    return -17;
                }

                tags.insert(std::make_pair(key, value));
                xmlTag = xmlTag->NextSiblingElement("tag");
            }

            way->setTags(tags);
            xmlWay = xmlWay->NextSiblingElement("way");

            ways.insert(std::make_pair(way->getId(), way));
        }


        tinyxml2::XMLElement* xmlRelation = osmRoot->FirstChildElement("relation");

        while(xmlRelation != nullptr){

            Relation* relation = new Relation();
            std::map<std::string, std::string> tags;
            const char* id = xmlRelation->Attribute("id");
            if(id == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                for(auto way : ways)
                    delete way.second;
                delete relation;
                return -18;
            }
            relation->setId(id);

            const char* userName = xmlRelation->Attribute("user");
            if(userName == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                for(auto way : ways)
                    delete way.second;
                delete relation;
                return -19;
            }
            relation->setUserName(userName);
            const char* userId = xmlRelation->Attribute("uid");
            if(userId == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                for(auto way : ways)
                    delete way.second;
                delete relation;
                return -20;
            }
            relation->setUserId(userId);

            const char* isVisible = xmlRelation->Attribute("visible");
            if(isVisible == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                for(auto way : ways)
                    delete way.second;
                delete relation;
                return -21;
            }
            relation->setIsVisible(strcmp(isVisible, "true") == 0);

            const char* version = xmlRelation->Attribute("version");
            if(version == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                for(auto way : ways)
                    delete way.second;
                delete relation;
                return -22;
            }
            relation->setVersion(version);

            const char* changeset = xmlRelation->Attribute("changeset");
            if(changeset == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                for(auto way : ways)
                    delete way.second;
                delete relation;
                return -23;
            }
            relation->setChangeset(changeset);

            const char* timestamp = xmlRelation->Attribute("timestamp");
            if(timestamp == nullptr)
            {
                for(auto node : nodes)
                    delete node.second;
                for(auto way : ways)
                    delete way.second;
                delete relation;
                return -24;
            }
            relation->setTimestamp(timestamp);

            tinyxml2::XMLElement* xmlConnected = xmlRelation->FirstChildElement("member");
            while(xmlConnected != nullptr){
                const char* type = xmlConnected->Attribute("type");
                const char* member_ref = xmlConnected->Attribute("ref");
                const char* role_pointer = xmlConnected->Attribute("role");
                if(type == nullptr || member_ref == nullptr || role_pointer == nullptr)
                {
                    for(auto node : nodes)
                        delete node.second;
                    for(auto way : ways)
                        delete way.second;
                    delete relation;
                    return -25;
                }
                std::string role(role_pointer);

                //relation->setType(type);
                if(strcmp(type, "node") == 0)

                    if(nodes.find(member_ref) != nodes.end())
                        relation->addNode(std::make_pair(nodes[member_ref], role));
                    else
                        relation->addNode(std::make_pair(nullptr, role));
                else if(strcmp(type, "way") == 0)
                    if(ways.find(member_ref) != ways.end())
                        relation->addWay(std::make_pair(ways[member_ref], role));
                    else
                        relation->addWay(std::make_pair(nullptr, role));
                else if(strcmp(type, "relation") == 0)
                    if(relations.find(member_ref) != relations.end())
                    {
                        relation->addRelation(std::make_pair(relations[member_ref], role));
                    } else
                    {
                        relation->addRelation(std::make_pair(nullptr, role));
                    }
                else
                {
                    for(auto node : nodes)
                        delete node.second;
                    for(auto way : ways)
                        delete way.second;
                    delete relation;
                    return -26;
                }

                xmlConnected = xmlConnected->NextSiblingElement("member");
            }


            tinyxml2::XMLElement* xmlTag = xmlRelation->FirstChildElement("tag");
            while(xmlTag != nullptr){
                const char* key = xmlTag->Attribute("k");
                const char* value = xmlTag->Attribute("v");
                if(key == nullptr || value == nullptr)
                {
                    for(auto node : nodes)
                        delete node.second;
                    for(auto way : ways)
                        delete way.second;
                    delete relation;
                    return -27;
                }

                tags.insert(std::make_pair(key, value));
                xmlTag = xmlTag->NextSiblingElement("tag");
            }

            relation->setTags(tags);
            xmlRelation = xmlRelation->NextSiblingElement("relation");

            relations.insert(std::make_pair(relation->getId(), relation));
        }
    } else
    {
        std::cerr << document.ErrorStr();
    }

    return 0;
}

int Root::save(std::string filename)
{
    std::ofstream ofs(filename);
    if(ofs.is_open())
    {
        ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
        ofs << "<osm version=\"" << version << "\" generator=\"" << generator << "\" copyright=\"" << copyright << "\" attribution=\"" << attribution << "\" license=\"" << license << "\" >" << std::endl;
        ofs << "\t<bounds minlat=\"" << min.x << "\" minlon=\"" << min.y << "\" maxlat=\"" << max.x << "\" maxlon=\"" << max.y << "\" />" << std::endl;
        for(auto node : nodes)
            ofs << node.second->toXML();
        for(auto way : ways)
            ofs << way.second->toXML();
        for(auto relation : relations)
            ofs << relation.second->toXML();
        ofs << "</osm>";
    } else
        return 1;
    return 0;
}
