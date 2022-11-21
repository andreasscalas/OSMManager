#ifndef OSMNODE_H
#define OSMNODE_H

#include <types.h>
#include <string>
#include <map>

namespace OpenStreetMap
{
    class Node
    {
    public:
        Node();
        ~Node();

        std::string getId() const;
        void setId(const std::string &value);

        std::string getUserName() const;
        void setUserName(const std::string &value);

        std::string getUserId() const;
        void setUserId(const std::string &value);

        std::string getVersion() const;
        void setVersion(const std::string &value);

        std::string getChangeset() const;
        void setChangeset(const std::string &value);

        bool isVisible() const;
        void setVisible(bool value);

        std::string getTimestamp() const;
        void setTimestamp(const std::string &value);

        void print(std::ostream &stream);
        std::string toXML();

        Point *getCoordinates() const;
        void setCoordinates(double x, double y);
        void setCoordinates(Point newCoordinates);
        void setCoordinates(Point *newCoordinates);

        const std::map<std::string, std::string> &getTags() const;
        void setTags(const std::map<std::string, std::string> &newTags);
        bool checkTag(const std::pair<std::string, std::string> tag) const;

    private:
        std::string id;
        std::string user_name;
        std::string user_id;
        std::string version;
        std::string changeset;
        std::string timestamp;
        Point* coordinates;
        bool is_visible;
        std::map<std::string, std::string> tags;

    };
}
#endif // OSMNODE_H
