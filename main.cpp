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

void display(Mat disp) {
    while(true) {
        imshow("Result", disp);
        if(waitKey(30) == 27) {
            return;
        }
    }

}

int main() {
    VideoCapture cam(0);
    Mat frame;
    outerloop:
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
        bool contour_check = contours.empty();
        if(!contour_check) {
            int largest_ind = largest_contour(contours);
            RotatedRect rec = minAreaRect(contours.at(largest_ind));
            vector<vector<Point>> draw;
            draw.emplace_back(contours.at(largest_ind));
            Mat clean = frame.clone();
            drawContours(frame, draw, -1, Scalar(255, 0, 0), 2, 8);
            if(waitKey(30) == 32) {
                double ratio = rec.size.height / rec.size.width;
                vector<Point2f> pts;
                int epsilon = 0;
                while(pts.size() != 4) {
                    epsilon++;
                    approxPolyDP(draw[0], pts, epsilon, true);
                }
                vector<Point2f> world_coors;
                int height = 1000 * ratio;
                cout << height << endl;
                world_coors.emplace_back(Point2f(0, 0));
                world_coors.emplace_back(Point2f(0, height));
                world_coors.emplace_back(Point2f(1000, height));
                world_coors.emplace_back(Point2f(1000, 0));
                Mat trans_mat = getPerspectiveTransform(pts, world_coors);
                Mat result = Mat(Size(1000, height), CV_64F);
                warpPerspective(clean, result, trans_mat, result.size());
//                destroyAllWindows();
//                waitKey(1);
                display(result);
                goto FINISH;
            }
        }

        imshow("Stream", frame);
        if(waitKey(30) == 27)
            break;
    }
    FINISH:return 0;
}

