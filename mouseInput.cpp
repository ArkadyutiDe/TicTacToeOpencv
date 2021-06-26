#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == cv::EVENT_RBUTTONDOWN) {
        std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == cv::EVENT_MBUTTONDOWN) {
        std::cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
    }
    else if (event == cv::EVENT_MOUSEMOVE) {
        std::cout << "Mouse move over the window - position (" << x << ", " << y << ")" << std::endl;
    }
}

void CallBack(int event, int x, int y, int flags, void * canvas) {
    cv::Mat frame = *(cv::Mat*) canvas;
    int radius = 50;

    if (event == cv::EVENT_LBUTTONDOWN) {
        cv::Point2i pt = cv::Point2i(x, y);
        cv::circle(frame, pt, radius, cv::Scalar(255, 255, 255));
    }
}

int main() {
    cv::Mat canvas(1000, 1000, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::namedWindow("MouseInput");
    cv::setMouseCallback("MouseInput", CallBack, &canvas);
    int k = -1;
    while (k != 27) {
        cv::imshow("MouseInput", canvas);
        k = cv::waitKey(33);
    }
    return 0;
}