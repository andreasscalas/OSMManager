#include "coordinatesconverter.h"
#include <string>

using namespace OpenStreetMap;

CoordsConverter::CoordsConverter(unsigned int epsg_utm)
{



    /* NOTE: the use of PROJ strings to describe CRS is strongly discouraged */
    /* in PROJ 6, as PROJ strings are a poor way of describing a CRS, and */
    /* more precise its geodetic datum. */
    /* Use of codes provided by authorities (such as "EPSG:4326", etc...) */
    /* or WKT strings will bring the full power of the "transformation */
    /* engine" used by PROJ to determine the best transformation(s) between */
    /* two CRS. */
    std::string epsg_from = "EPSG:" + std::to_string(epsg_utm);
    P1 = proj_create_crs_to_crs(0,
                               epsg_from.c_str(),
                               "EPSG:4326",
                               NULL);
    P2 = proj_create_crs_to_crs(0,
                               "EPSG:4326",
                               epsg_from.c_str(),
                               NULL);




  //  pj_longlat = pj_init_plus("+init=epsg:4326" );
  //  pj_utm = pj_init_plus('+init=epsg:' + std::to_string(epsg_utm).c_str() );

}

void CoordsConverter::convertToWgs84(double x_utm, double y_utm, double &lat, double &lon)
{

    PJ_COORD c, c_out;

    c.xyz.x = x_utm;
    c.xyz.y = y_utm;
    c.xyz.z = 0;
    if(P1 != nullptr)
    {
        c_out = proj_trans( P1, PJ_FWD, c );
        lat = c_out.lp.lam;
        lon = c_out.lp.phi;
    }

}

void CoordsConverter::convertToUTM(double lat, double lon, double &x_utm, double &y_utm)
{

    PJ_COORD c, c_out;

    c.lp.phi = lon;
    c.lp.lam = lat;
    c.xyz.z = 0;
    if(P2 != nullptr)
    {
        c_out = proj_trans( P2, PJ_FWD, c );
        x_utm = c_out.xyz.x;
        y_utm = c_out.xyz.y;
    }
}
