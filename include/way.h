#ifndef OSMWAY_H
#define OSMWAY_H

#include <node.h>
#include <memory>
#include <vector>

namespace OpenStreetMap
{
    class Way
    {
    public:
        Way();
        std::string getId() const;
        void setId(const std::string &value);

        bool removeNode(std::string id);
        const std::vector<Node *> &getNodes() const;
        void setNodes(const std::vector<Node *> &newNodes);

        std::string getUserName() const;
        void setUserName(const std::string &value);

        std::string getUserId() const;
        void setUserId(const std::string &value);

        bool getIsVisible() const;
        void setIsVisible(bool value);

        std::string getVersion() const;
        void setVersion(const std::string &value);

        std::string getChangeset() const;
        void setChangeset(const std::string &value);

        bool checkTag(std::pair<std::string, std::string> tag);
        const std::map<std::string, std::string> &getTags() const;
        void setTags(const std::map<std::string, std::string> &newTags);

        std::string getTimestamp() const;
        void setTimestamp(const std::string &value);

        std::string toXML();

    private:
        std::string id;
        std::vector<Node*> nodes;
        std::string user_name;
        std::string user_id;
        bool is_visible;
        std::string version;
        std::string changeset;
        std::string timestamp;
        std::map<std::string, std::string> tags; //Array of pairs <key, value>

    };
}
#endif // OSMWAY_H
