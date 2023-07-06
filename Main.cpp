#include <opencv2/opencv.hpp>
#include "Polygon.h"

int main(int argc, const char * argv[])
{
    const std::string path_to_file = "../Polygon_dots";
    int coordinate_x, coordinate_y, width, length, condition;

    polygon polygon(path_to_file);

    polygon.add_dot_to_polygon(10, 10);
    polygon.add_dot_to_polygon(1, -1);
    polygon.add_dot_to_polygon(-5, 5);
    polygon.add_dot_to_polygon(5, -5);

    std::cout << "Enter rectangle position and size:" << std::endl;
    std::cout << "X: ";
    std::cin >> coordinate_x;
    std::cout << "Y: ";
    std::cin >> coordinate_y;
    std::cout << "Width: ";
    std::cin >> width;
    std::cout << "Height: ";
    std::cin >> length;

    std::cout << "Choose condition (1 - any point, 2 - all points, 3 - center): ";
    std::cin >> condition;

    bool interposition = polygon.check_figure_interposition(coordinate_x, coordinate_y, length, width, condition);

    if (interposition)
    {
        std::cout << "The rectangle intersects the polygon" << std::endl;
    }
    else
    {
        std::cout << "The rectangle does not intersect the polygon" << std::endl;
    }
    return 0;
}
