#ifndef OSM_OBJECT_H
#define OSM_OBJECT_H

#include <string>
#include <map>

namespace OpenStreetMap
{
    class Object
    {
    public:
        Object();
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

        virtual void print(std::ostream &stream);
        virtual std::string toXML();

        const std::map<std::string, std::string> &getTags() const;
        void setTags(const std::map<std::string, std::string> &newTags);
        void addTag(std::pair<std::string, std::string> newTag);
        bool checkTag(const std::pair<std::string, std::string> tag) const;

    protected:
        std::string id;
        std::string user_name;
        std::string user_id;
        std::string version;
        std::string changeset;
        std::string timestamp;
        bool is_visible;
        std::map<std::string, std::string> tags;
    };
}

#endif // OSM_OBJECT_H
