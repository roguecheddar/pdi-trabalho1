#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void additBrighten(Mat& image, const int beta);

int multiBrighten(Mat& image, const float c);

void negative(Mat& image);

Mat rgb2yiq(Mat& image);

Mat yiq2rgb(Mat& image);