#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int largest_contour(vector<vector<Point>> &contours) {
    int ind = 0;
    int size = 0;
    for(int i = 0; i < contours.size(); i++) {
        int area = contourArea(contours.at(i));
        if(area > size) {
            ind = i;
            size = area;
        }
    }
    return ind;
}

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
    findContours(canny, contours, noArray(), RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//    drawContours(img, contours, -1, Scalar(0, 0, 255), -1, 8);
    int largest_ind = largest_contour(contours);
    RotatedRect rec = minAreaRect(contours.at(largest_ind));
//    vector<Point2f> corners(4);
//    rec.points(corners.data());
    vector<vector<Point>> draw;
    draw.emplace_back(contours.at(largest_ind));
    drawContours(img, draw, -1, Scalar(0, 0, 255), 2, 8);
//    vector<Point> corners
//    boxPoints(rec, corners);
//    for(int i = 0; i < corners.size(); i++) {
//        circle(img, corners.at(i), 5, Scalar(0, 0, 255), -1);
//    }

    vector<Point> pts(4);
    approxPolyDP(draw[0], pts, 5, true);
    for(int i = 0; i < pts.size(); i++) {
        circle(img, pts.at(i), 5, Scalar(0, 0, 255), -1);
    }
    //display image
    imshow("Image", img);
    waitKey(0);
    return 0;
}
