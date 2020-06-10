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

int main() {
    VideoCapture cam(0);
    Mat frame;
    while(true) {
        cam >> frame;
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);
//        blur image
        Mat blurred;
        bilateralFilter(gray, blurred, 5, 75, 75);
//        apply canny edge detection to image
        Mat canny;
        Canny(blurred, canny, 60, 150);
        //find contours of image
        vector<vector<Point>> contours;
        findContours(canny, contours, noArray(), RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        drawContours(frame, contours, -1, Scalar(0, 0, 0), 1, 8);
        imshow("Stream", frame);
//        sleep(1);
        if(waitKey(30) == 27)
            break;
    }
    return 0;
}

//int main()
//{
//    //read image
//    Mat img = imread("card.jpg", IMREAD_COLOR);
//    //convert image to grayscale
//    Mat gray;
//    cvtColor(img, gray, COLOR_BGR2GRAY);
//    //blur image
//    Mat blurred;
//    bilateralFilter(gray, blurred, 5, 75, 75);
//    //apply canny edge detection to image
//    Mat canny;
//    Canny(blurred, canny, 60, 150);
//    //find contours of image
//    vector<vector<Point>> contours;
//    findContours(canny, contours, noArray(), RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//    //find largest contour in image
//    int largest_ind = largest_contour(contours);
//    RotatedRect rec = minAreaRect(contours.at(largest_ind));
//    vector<vector<Point>> draw;
//    draw.emplace_back(contours.at(largest_ind));
////    drawContours(img, draw, -1, Scalar(0, 0, 255), 2, 8);
////    vector<Point> corners
////    boxPoints(rec, corners);
////    for(int i = 0; i < corners.size(); i++) {
////        circle(img, corners.at(i), 5, Scalar(0, 0, 255), -1);
////    }
//    double ratio = rec.size.height / rec.size.width;
//    cout << ratio << endl;
//    vector<Point2f> pts;
//    int epsilon = 0;
//    while(pts.size() != 4) {
//        epsilon++;
//        approxPolyDP(draw[0], pts, epsilon, true);
//    }
////    circle(img, pts.at(0), 5, Scalar(255, 0, 0), -1); //blue
////    circle(img, pts.at(1), 5, Scalar(0, 255, 0), -1); //green
////    circle(img, pts.at(2), 5, Scalar(0, 0, 255), -1); //red
////    circle(img, pts.at(3), 5, Scalar(0, 0, 0), -1); //black
//    //    for(int i = 0; i < pts.size(); i++) {
////        circle(img, pts.at(i), 5, Scalar(0, 0, 255), -1);
////    }
//    vector<Point2f> world_coors;
//    int height = 1000 * ratio;
//    cout << height << endl;
//    world_coors.emplace_back(Point2f(0, 0));
//    world_coors.emplace_back(Point2f(0, height));
//    world_coors.emplace_back(Point2f(1000, height));
//    world_coors.emplace_back(Point2f(1000, 0));
//    Mat trans_mat = getPerspectiveTransform(pts, world_coors);
//    Mat result = Mat(Size(1000, height), CV_64F);
//    warpPerspective(img, result, trans_mat, result.size());
////    perspectiveTransform(pts, result, trans_mat);
//    //display image
//    imshow("Image", result);
//    waitKey(0);
//    return 0;
//}


