#include "Polygon.h"

polygon::polygon(const std::string& path_to_file)
{
    polygon_init(path_to_file);
}

void polygon::print_polygon_dots()
{
    for(int i = 0; i < polygon_dots.size(); i++)
    {
        std::cout << i << " point: X = " << polygon_dots[i].x << ", Y = " << polygon_dots[i].y << std::endl;
    }
}

std::vector<cv::Point>& polygon::get_polygon()
{
    return polygon_dots;
}

void polygon::add_dot_to_polygon(int coordinate_x, int coordinate_y)
{
    polygon_dots.emplace_back(coordinate_x, coordinate_y);//Push to end of vector
}

void polygon::polygon_init(const std::string& path_to_file)
{
    std::ifstream file(path_to_file);//Open stream
    if (file.is_open())
    {
        int coordinate_x, coordinate_y;
        while (file >> coordinate_x >> coordinate_y)//Read from stream
        {
            add_dot_to_polygon(coordinate_x, coordinate_y);
        }
        file.close();
    }
    else
        std::cerr << "Unable to open file" << std::endl;
}

bool polygon::check_figure_interposition(int coordinate_x, int coordinate_y, int length, int width, int condition)
{
    // Check if any point of the rectangle is inside the polygon
    if (condition == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (check_point_in_polygon(coordinate_x + i % 2 * width, coordinate_y + i / 2 * length))
                return true;
        }
        return false;
    }
    // Check if all points of the rectangle are inside the polygon
    else if (condition == 2)
    {
        for (int i = 0; i < 4; i++)
        {
            if (!check_point_in_polygon(coordinate_x + i % 2 * width, coordinate_y + i / 2 * length))
                return false;
        }
        return true;
    }
    // Check if the center of the rectangle is inside the polygon
    else if (condition == 3)
    {
        int center_x = coordinate_x + width / 2;
        int center_y = coordinate_y + length / 2;
        return check_point_in_polygon(center_x, center_y);
    }
    return false;
}

bool polygon::check_point_in_polygon(int coordinate_x, int coordinate_y)
{
    bool inside = false; // Point location flag

    for (size_t i = 0, j = polygon_dots.size() - 1; i < polygon_dots.size(); j = i++)
    {
        if (((polygon_dots[i].y > coordinate_y) != (polygon_dots[j].y > coordinate_y)) &&
            (coordinate_x < (polygon_dots[j].x - polygon_dots[i].x) * (coordinate_y - polygon_dots[i].y) / (polygon_dots[j].y - polygon_dots[i].y) + polygon_dots[i].x))
        {
            inside = !inside;
        }
    }
    return inside;
}

