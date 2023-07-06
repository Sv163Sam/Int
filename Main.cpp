#include "Polygon.h"
#define WINDOW_NAME "Drawing window"

void on_mouse_handle(int event, int coordinate_x, int coordinate_y, int flags, void* param);//Implementing mouse action
void draw_rectangle(cv::Mat& image, cv::Rect box);//Rectangle drawing process

cv::Rect g_rectangle;//Rectangle
cv::RNG g_rng(0);//Generate random number
bool g_b_drawing_box = false;//Rectangle status flag


int main(int argc, const char * argv[])
{
    int coordinate_x, coordinate_y, width, length, condition;//Task var for init

    const std::string path_to_file = "../Polygon_dots";
    polygon polygon(path_to_file);//Create a polygon

    int mode = 1;
    std::cout << "Please enter a program mode:\n1 - Realtime draw\n2 - Rectangle coordinates by keyboard" << std::endl;
    std::cin >> mode;

    switch(mode)
    {
        case 1:
        {
            cv::Mat src_image(600, 800, CV_8UC3);//Create main window
            cv::Mat temp_image;//Create temp window

            src_image = cv::Scalar::all(0);//Color assignment

            cv::namedWindow(WINDOW_NAME); //Rename a window
            cv::setMouseCallback(WINDOW_NAME, on_mouse_handle, (void*) &src_image);//Set mouse connection

            while (true)
            {
                src_image.copyTo(temp_image);
                //Draw a polygon with random color
                cv::polylines(temp_image, polygon.get_polygon(), true,
                              cv::Scalar(g_rng.uniform(0, 255),
                                         g_rng.uniform(0,255),g_rng.uniform(0,255)), 1);
                if (g_b_drawing_box)
                    draw_rectangle(temp_image, g_rectangle);

                imshow(WINDOW_NAME, temp_image);//Show current window

                if (cv::waitKey(10) == 32)  // stop drawing rectangle if the key is 'Space'
                {
                    coordinate_x = g_rectangle.x;
                    coordinate_y = g_rectangle.y;
                    width = g_rectangle.width;
                    length = g_rectangle.height;
                    std::cout << "Choose condition: \n1 - Any point\n2 - All points\n3 - Center" << std::endl;
                    std::cin >> condition;
                    bool interposition = polygon.check_figure_interposition(coordinate_x, coordinate_y, length, width,
                                                                            condition);
                    if (interposition)
                        std::cout << "The rectangle intersects the polygon" << std::endl;
                    else
                        std::cout << "The rectangle does not intersect the polygon" << std::endl;
                    break;
                }
            }
        }
        break;
        case 2:
        {
            polygon.print_polygon_dots();
            std::cout << "Enter rectangle position and size:" << std::endl;
            std::cout << "X: ";
            std::cin >> coordinate_x;
            std::cout << "Y: ";
            std::cin >> coordinate_y;
            std::cout << "Width: ";
            std::cin >> width;
            std::cout << "Height: ";
            std::cin >> length;

            std::cout << "Choose condition: \n1 - Any point\n2 - All points\n3 - Center" << std::endl;
            std::cin >> condition;
            bool interposition = polygon.check_figure_interposition(coordinate_x, coordinate_y, length, width, condition);
            if (interposition)
                std::cout << "The rectangle intersects the polygon" << std::endl;
            else
                std::cout << "The rectangle does not intersect the polygon" << std::endl;
        }
        break;
        default:
            return 0;
    }
}

void on_mouse_handle(int event, int coordinate_x, int coordinate_y, int flags, void* param)
{
    cv::Mat& image = *(cv::Mat*) param;
    switch (event)
    {
        case cv::EVENT_MOUSEMOVE:
        {
            // When mouse moves, get the current rectangle's width and height
            if (g_b_drawing_box)
            {
                g_rectangle.width = coordinate_x - g_rectangle.x;
                g_rectangle.height = coordinate_y - g_rectangle.y;
            }
        }
            break;
        case cv::EVENT_LBUTTONDOWN:
        {
            // when the left mouse button is pressed down,
            //get the starting corner's coordinates of the rectangle
            g_b_drawing_box = true;
            g_rectangle = cv::Rect(coordinate_x, coordinate_y, 0, 0);
        }
            break;
        case cv::EVENT_LBUTTONUP:
        {
            //when the left mouse button is released,
            //draw the rectangle
            g_b_drawing_box = false;
            if (g_rectangle.width < 0)
            {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }
            if (g_rectangle.height < 0)
            {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *= -1;
            }
            draw_rectangle(image, g_rectangle);
        }
            break;
        default:
            break;
    }
}
void draw_rectangle(cv::Mat& image, cv::Rect box)
{
    //Draw a rectangle with random color
    rectangle(image, box.tl(), box.br(), cv::Scalar(g_rng.uniform(0, 255),
                                              g_rng.uniform(0,255),g_rng.uniform(0,255)));
}