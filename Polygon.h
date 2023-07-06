#ifndef Polygon_h
#define Polygon_h

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>


class polygon
{
private:
    std::vector<cv::Point> polygon_dots; //Contain all polygon dots
    bool check_point_in_polygon(int coordinate_x, int coordinate_y);//Func allows to check that the polygon contains a point
public:
    explicit polygon(const std::string& path_to_file);//Constructor with params
    std::vector<cv::Point>& get_polygon();//Getter(All polygon dots)
    void add_dot_to_polygon(int coordinate_x, int coordinate_y);//Func allows to add a point to a polygon
    void polygon_init(const std::string& path_to_file);//Read polygon dots from file
    bool check_figure_interposition(int coordinate_x, int coordinate_y, int length, int width, int condition);//Func allows to check a condition
    void print_polygon_dots();//Show all polygon dots
};


#endif /* Polygon_h */
