#ifndef OSM_COORDINATESCONVERTER_H
#define OSM_COORDINATESCONVERTER_H

#include <proj.h>

namespace OpenStreetMap
{
    class CoordsConverter
    {
    public:
        CoordsConverter(unsigned int epsg_utm);

        void convertToWgs84(double x_utm, double y_utm, double &lat, double &lon);
        void convertToUTM(double lat, double lon, double &x_utm, double &y_utm);

    private:

        PJ* P1;
        PJ* P2;


    };
}
#endif // OSM_COORDINATESCONVERTER_H
