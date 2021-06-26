#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// ascii values of keyboard keys.
#define ESCAPE 27
#define RIGHT 83
#define LEFT 81
#define UP 82
#define DOWN 84

int main() {

    cv::Mat background(1000, 1000, CV_8UC3, cv::Scalar(255, 0, 0));
    int radius = 100, val = 2, p1 = 500, p2 = 500;
    cv::Point2i pt = cv::Point2i(p1, p2);

    while (val != 0) {

        cv::Mat frame = background.clone();
        cv::circle(frame, pt, radius, cv::Scalar(255, 255, 255));

        cv::imshow("DisplayWindow", frame);
        int k = cv::waitKey(33); // waiting for 33 milliseconds..

        if (k == ESCAPE) {
            break;
        }

        switch(k) {
            case RIGHT:
                p1 = p1 + 100;
                if (p1 > frame.cols) p1 = 0;
                if (p1 < 0) p1 = 0;
                pt = cv::Point2i(p1, p2);
                break;

            case LEFT:
                p1 = p1 - 100;
                if (p1 > frame.cols) p1 = frame.cols;
                if (p1 < 0) p1 = frame.cols;
                pt = cv::Point2i(p1, p2);
                break;

            case UP:
                p2 = p2 - 100;
                if (p2 > frame.rows) p2 = frame.rows;
                if (p2 < 0) p2 = frame.rows;
                pt = cv::Point2i(p1, p2);
                break;

            case DOWN:
                p2 = p2 + 100;
                if (p2 > frame.rows) p2 = 0;
                if (p2 < 0) p2 = 0;
                pt = cv::Point2i(p1, p2);
                break;
        }

    }

    return 0;
}