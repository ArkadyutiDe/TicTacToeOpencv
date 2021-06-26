#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

int main() {
    cv::Mat img(1000, 1000, CV_8UC3);
    cv::Point pt = cv::Point(0, 75), pt1 = cv::Point(200, 100), pt2 = cv::Point(800, 500), pt3 = cv::Point(150, 50), pt4 = cv::Point(130, 80);
    cv::Point pt5 = cv::Point(600, 600), pt6 = cv::Point(400, 600), pt7 = cv::Point(600, 800);
    int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX, radius = 180,radius2 = 120, thickness = -(radius2), val = 2;
    double fontSize = 2;

    cv::rectangle(img, pt1, pt2,cv::Scalar(255, 0, 0));
    cv::putText(img, "My Rectangle, Triangle and Circles..", pt, fontFace, fontSize, cv::Scalar(0, 255, 0));
    cv::circle(img, pt2, radius, cv::Scalar(0, 0, 255));
    cv::circle(img, pt2, radius2, cv::Scalar(0, 255, 255), thickness);
    cv::line(img, pt5, pt6, cv::Scalar(255, 255, 0));
    cv::line(img, pt7, pt6, cv::Scalar(255, 255, 0));
    cv::line(img, pt7, pt5, cv::Scalar(255, 255, 0));

    while (val != 0) {
        cv::imshow("DisplayWindow", img);
        int k = cv::waitKey(33);
        if (k == 27) {
            break;
        }
        else {
            if (k != -1) {
                std::cout << k << " was pressed" << std::endl;
            }
        }
    }

    return 0;
}