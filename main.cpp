#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
    //read image
    Mat img = imread("card.jpg", IMREAD_COLOR);
    //convert image to grayscale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    //blur image
    Mat blurred;
    bilateralFilter(gray, blurred, 5, 75, 75);
    //apply canny edge detection to image
    Mat canny;
    Canny(blurred, canny, 60, 150);
//    vector<Point2f> corners;
//    goodFeaturesToTrack(blurred, corners, 100, 0.05, 10, noArray(), 3, true);
////    cornerHarris(blurred, img, 2, 2, 0.04);
//    for(Point2f &corner : corners)
//        circle(img, corner, 5, Scalar(0, 0, 255), -1);
    //find and draw contours of image
    vector<vector<Point>> contours;
    findContours(canny, contours, noArray(), RETR_CCOMP, CHAIN_APPROX_SIMPLE);
    drawContours(img, contours, -1, Scalar(0, 0, 255), -1, 8);
    //display image
    imshow("Image", img);
    waitKey(0);
    return 0;
}
