#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "project_tools.h"

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	char* source = "../data/boss.jpg";

    Mat image;
	Mat new_image;
	Mat image_color;
    image = imread(source, CV_LOAD_IMAGE_GRAYSCALE);   // Read the file
	image_color = imread(source, CV_LOAD_IMAGE_COLOR);

	new_image = Mat::zeros(image.size(), image.type());

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
		
	//multiBrighten(image_color, 100.0);
	//rgb2yiq(image_color);

	namedWindow("Display window", WINDOW_AUTOSIZE);	// Create a window for display.

    imshow( "Display window", yiq2rgb(rgb2yiq(image_color)));                   // Show our image inside it.	

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
	}