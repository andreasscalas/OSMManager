#ifndef OSM_OSMNODE_H
#define OSM_OSMNODE_H

#include "types.h"
#include "object.h"
#include <string>
#include <map>

namespace OpenStreetMap
{
    class Node : public Object
    {
    public:
        Node();
        virtual ~Node();

        Point *getCoordinates() const;
        void setCoordinates(double x, double y);
        void setCoordinates(Point newCoordinates);
        void setCoordinates(Point *newCoordinates);

        virtual void print(std::ostream &stream) override;
        virtual std::string toXML() override;

    private:
        Point* coordinates;

    };
}
#endif // OSM_OSMNODE_H
