#ifndef OSMRELATION_H
#define OSMRELATION_H

#include <node.h>
#include <way.h>

namespace OpenStreetMap
{
    class Relation
    {
    public:
        Relation();

        std::string getId() const;
        void setId(const std::string &value);

        const std::map<Node *, std::string> &getNodes() const;
        void setNodes(const std::map<Node *, std::string> &newNodes);
        bool addNode(const std::pair<Node*, std::string> node);
        bool removeNode(Node*);
        bool removeNode(std::string osmid);

        const std::map<Way *, std::string> &getWays() const;
        void setWays(const std::map<Way *, std::string> &newWays);
        bool addWay(const std::pair<Way*, std::string> way);
        bool removeWay(Way*);
        bool removeWay(std::string osmid);

        const std::map<Relation *, std::string> &getRelations() const;
        void setRelations(const std::map<Relation *, std::string> &newRelations);
        bool addRelation(const std::pair<Relation*, std::string> relation);
        bool removeRelation(Relation*);
        bool removeRelation(std::string osmid);

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

        const std::map<std::string, std::string> &getTags() const;
        void setTags(const std::map<std::string, std::string> &newTags);
        bool checkTag(std::pair<std::string, std::string> tag);

        std::string getTimestamp() const;
        void setTimestamp(const std::string &value);

        std::string toXML();

    private:
        std::string id;
        std::map<Node*, std::string > nodes;
        std::map<Way*, std::string> ways;
        std::map<Relation*, std::string> relations;
        std::string user_name;
        std::string user_id;
        bool is_visible;
        std::string version;
        std::string changeset;
        std::string timestamp;
        std::map<std::string, std::string> tags;
    };

}
#endif // OSMRELATION_H
