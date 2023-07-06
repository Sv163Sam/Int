#include "Polygon.h"

polygon::polygon(const std::string& path_to_file)
{
    polygon_init(path_to_file);
}

void polygon::add_dot_to_polygon(int coordinate_x, int coordinate_y)
{
    point dot{};
    dot.coordinate_x = coordinate_x;
    dot.coordinate_y = coordinate_y;
    polygon_dots.push_back(dot);
}

void polygon::polygon_init(const std::string& path_to_file)
{
    std::ifstream file(path_to_file);
    if (file.is_open())
    {
        int coordinate_x;
        int coordinate_y;
        while (file >> coordinate_x >> coordinate_y)
        {
            add_dot_to_polygon(coordinate_x, coordinate_y);
        }
        file.close();
    }
        //
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
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
        int centerX = coordinate_x + width / 2;
        int centerY = coordinate_y + length / 2;
        return check_point_in_polygon(centerX, centerY);
    }
    return false;
}

bool polygon::check_point_in_polygon(int coordinate_x, int coordinate_y)
{
    size_t i, j;
    bool inside = false;

    for (i = 0, j = polygon_dots.size() - 1; i < polygon_dots.size(); j = i++)
    {
        if (((polygon_dots[i].coordinate_y > coordinate_y) != (polygon_dots[j].coordinate_y > coordinate_y)) &&
            (coordinate_x < (polygon_dots[j].coordinate_x - polygon_dots[i].coordinate_x) * (coordinate_y - polygon_dots[i].coordinate_y) / (polygon_dots[j].coordinate_y - polygon_dots[i].coordinate_y) + polygon_dots[i].coordinate_x))
        {
            inside = !inside;
        }
    }
    return inside;
}

