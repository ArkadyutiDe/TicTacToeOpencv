#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

cv::Mat getBoard() {
    cv::Mat frame(900, 900, CV_8UC3, cv::Scalar(0, 0, 255));
    int thickness = 5;
    cv::Point pt1 = cv::Point(0, 300), pt2 = cv::Point(900, 300);
    cv::line(frame, pt1, pt2, cv::Scalar(0, 255, 255), thickness);
    cv::Point pt3 = cv::Point(0, 600), pt4 = cv::Point(900, 600);
    cv::line(frame, pt3, pt4, cv::Scalar(0, 255, 255), thickness);
    cv::Point pt5 = cv::Point(300, 0), pt6 = cv::Point(300, 900);
    cv::line(frame, pt5, pt6, cv::Scalar(0, 255, 255), thickness);
    cv::Point pt7 = cv::Point(600, 0), pt8 = cv::Point(600, 900);
    cv::line(frame, pt7, pt8, cv::Scalar(0, 255, 255), thickness);
    return frame;
}

void CallTicTacToe(int event, int x, int y , int flags, void * canvas) {
    cv::Mat frame = *(cv::Mat*)canvas;
    cv::Point2i pt;
    int radius = 100, thickness = 2, count = 0;

    if (event == cv::EVENT_LBUTTONUP) {
        if (x < 300) {
            if (y < 300) {
                pt = cv::Point2i(150, 150);
                count = 1;
            }
            else {
                if ( y < 600) {
                    pt = cv::Point2i(150, 450);
                    count = 1;
                }
                else {
                    pt = cv::Point2i(150, 750);
                    count = 1;
                }
            }
        }
        else if (x < 600) {
            if (y < 300) {
                pt = cv::Point2i(450, 150);
                count = 1;
            }
            else {
                if ( y < 600) {
                    pt = cv::Point2i(450, 450);
                    count = 1;
                }
                else {
                    pt = cv::Point2i(450, 750);
                    count = 1;
                }
            }
        }
        else if (x < 900) {
            if (y < 300) {
                pt = cv::Point2i(750, 150);
                count = 1;
            }
            else {
                if ( y < 600) {
                    pt = cv::Point2i(750, 450);
                    count = 1;
                }
                else {
                    pt = cv::Point2i(750, 750);
                    count = 1;
                }
            }
        }
    }
    if (count == 1) {
        cv::circle(frame, pt, radius, cv::Scalar(0, 255, 255), thickness);
    }
}

int main() {
    cv::Mat board = getBoard();
    cv::namedWindow("Board");
    cv::setMouseCallback("Board", CallTicTacToe, &board);

    int k = -1;

    while (k != 27) {
        cv::imshow("Board", board);
        k = cv::waitKey(33);
    }

    return 0;
}