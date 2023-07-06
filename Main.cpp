#include "Polygon.h"

#define WINDOW_NAME "Drawing Rectangle"

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);

cv::Rect g_rectangle;
bool g_bDrawingBox = false;
cv::RNG g_rng(0);  // Generate random number


int main(int argc, const char * argv[])
{
    int coordinate_x, coordinate_y, width, length, condition;

    const std::string path_to_file = "../Polygon_dots";
    polygon polygon(path_to_file);

    int mode = 1;
    std::cout << "Please enter a program mode:\n1 - Realtime draw\n2 - Rectangle coordinates by keyboard" << std::endl;
    std::cin >> mode;

    switch(mode)
    {
        case 1:
        {
            cv::Mat srcImage(600, 800, CV_8UC3);
            cv::Mat tempImage;

            srcImage = cv::Scalar::all(0);

            cv::namedWindow(WINDOW_NAME);
            cv::setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*) &srcImage);


            srcImage.copyTo(tempImage);

            cv::polylines(tempImage, polygon.get_polygon(), true,
                          cv::Scalar(0, 0, 255), 2);

            while (true)
            {
                if (g_bDrawingBox)
                    DrawRectangle(tempImage, g_rectangle);

                imshow(WINDOW_NAME, tempImage);

                if (cv::waitKey(10) == 27)  // stop drawing rectangle if the key is 'Enter'
                {
                    coordinate_x = g_rectangle.x;
                    coordinate_y = g_rectangle.y;
                    width = g_rectangle.width;
                    length = g_rectangle.height;

                    std::cout << "Choose condition: \n1 - Any point\n2 - All points\n3 - Center" << std::endl;
                    std::cin >> condition;

                    bool interposition = polygon.check_figure_interposition(coordinate_x, coordinate_y, length, width,
                                                                            condition);

                    if (interposition) {
                        std::cout << "The rectangle intersects the polygon" << std::endl;
                    } else {
                        std::cout << "The rectangle does not intersect the polygon" << std::endl;
                    }
                    break;
                }
            }
        }
        break;
        case 2:
        {
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
            {
                std::cout << "The rectangle intersects the polygon" << std::endl;
            }
            else
            {
                std::cout << "The rectangle does not intersect the polygon" << std::endl;
            }
        }
        break;
        default:
            return 0;
    }
}

void on_MouseHandle(int event, int x, int y, int flags, void* param) {
    cv::Mat& image = *(cv::Mat*) param;
    switch (event) {
        case cv::EVENT_MOUSEMOVE: {    // When mouse moves, get the current rectangle's width and height
            if (g_bDrawingBox) {
                g_rectangle.width = x - g_rectangle.x;
                g_rectangle.height = y - g_rectangle.y;
            }
        }
            break;
        case cv::EVENT_LBUTTONDOWN: {  // when the left mouse button is pressed down,
            //get the starting corner's coordinates of the rectangle
            g_bDrawingBox = true;
            g_rectangle = cv::Rect(x, y, 0, 0);
        }
            break;
        case cv::EVENT_LBUTTONUP: {   //when the left mouse button is released,
            //draw the rectangle
            g_bDrawingBox = false;
            if (g_rectangle.width < 0) {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }

            if (g_rectangle.height < 0) {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *= -1;
            }
            DrawRectangle(image, g_rectangle);
        }
            break;
    }
}
void DrawRectangle(cv::Mat& img, cv::Rect box)
{
    //Draw a rectangle with random color
    rectangle(img, box.tl(), box.br(), cv::Scalar(g_rng.uniform(0, 255),
                                              g_rng.uniform(0,255),g_rng.uniform(0,255)));
}