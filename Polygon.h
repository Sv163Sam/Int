#ifndef Polygon_h
#define Polygon_h

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class polygon
{
private:
    struct point
    {
        int coordinate_x;
        int coordinate_y;
    };
    std::vector<point> polygon_dots;
    bool check_point_in_polygon(int coordinate_x, int coordinate_y);
public:
    explicit polygon(const std::string& path_to_file);
    void add_dot_to_polygon(int coordinate_x, int coordinate_y);
    void polygon_init(const std::string& path_to_file);
    bool check_figure_interposition(int coordinate_x, int coordinate_y, int length, int width, int condition);
};


#endif /* Polygon_h */
