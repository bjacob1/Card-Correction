#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    Mat img = imread("card.jpg", IMREAD_COLOR);
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    Mat blurred;
    bilateralFilter(gray, blurred, 5, 75, 75);
    vector<Point2f> corners;
    goodFeaturesToTrack(blurred, corners, 4, 0.01, 1);
    for(Point2f &corner : corners)
        circle(img, corner, 5, Scalar(0, 0, 255), -1);
    imshow("Image", blurred);
    waitKey(1);
    return 0;
}
