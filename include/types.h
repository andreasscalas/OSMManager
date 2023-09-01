#ifndef OSM_TYPES_H
#define OSM_TYPES_H

namespace OpenStreetMap {
    class Point
    {
    public:
        double x, y;
        constexpr static const double EPSILON = 1e-5;
        Point()
        {
        }

        Point(double x, double y)
        {
            this->x = x;
            this->y = y;
        }

        inline bool operator==(const Point p) const
        {
            return p.x < x + EPSILON && p.x > x - EPSILON &&
                   p.y < y + EPSILON && p.y > y - EPSILON;
        }

        inline bool operator!=(const Point other) const
        {
            return !(*this==other);
        }

        inline Point operator+(const Point other) const
        {
            return Point(x + other.x, y + other.y);
        }

        inline void operator+=(const Point other)
        {
            this->x = x + other.x;
            this->y = y + other.y;
        }

        inline Point operator-(const Point other) const
        {
            return Point(x - other.x, y - other.y);
        }

        inline void operator-=(const Point other)
        {
            this->x = x - other.x;
            this->y = y - other.y;
        }

        inline double operator*(const Point other) const
        {
            return x * other.x + y * other.y;
        }

        inline Point operator*(const double val) const
        {
            return Point(x * val, y * val);
        }

        inline void operator*=(const double val)
        {
            x = x * val;
            y = y * val;
        }

        inline Point operator/(const double val) const
        {
            return Point(x / val, y / val);
        }

        inline void operator/=(const double val)
        {
            x = x / val;
            y = y / val;
        }

        inline void operator=(const Point other)
        {
            this->x = other.x;
            this->y = other.y;
        }
    };
}


#endif // OSM_TYPES_H
