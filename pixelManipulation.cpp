#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

#define WIDTH 800

void kotkota(cv::Mat img, cv::Scalar searchColor, cv::Scalar kotkotaColor = cv::Scalar(255, 0, 0)) {
    for (int r = 0; r < img.rows; r++) {
        for (int c = 0; c <img.cols; c++) {
            uchar blue  = img.at<Vec3b>(r, c)[0];
            uchar green = img.at<Vec3b>(r, c)[1];
            uchar red   = img.at<Vec3b>(r, c)[2];
            if (blue == searchColor[0] && green == searchColor[1] && red == searchColor[2]) {
                img.at<Vec3b>(r, c)[0] = kotkotaColor[0];
                img.at<Vec3b>(r, c)[1] = kotkotaColor[1];
                img.at<Vec3b>(r, c)[2] = kotkotaColor[2];
            }
        }
    }
    cv::imshow("Kotkota", img);
    cv::waitKey(0);
}

bool isPresent(uchar r,uchar g,uchar b,uchar rC[],uchar gC[],uchar bC[], int c) {
    for (int i = 0; i < c; i++) {
        if (r == rC[i] && g == gC[i] && b == bC[i]) {
            return true;
        }
    }
    return false;
}

void playColors(cv::Mat img) {
    uchar blueC[img.rows * img.cols];
    uchar greenC[img.rows * img.cols];
    uchar redC[img.rows * img.cols];
    int count = 0;

    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            uchar blue  = img.at<Vec3b>(y,x)[0];
            uchar green = img.at<Vec3b>(y,x)[1];
            uchar red   = img.at<Vec3b>(y,x)[2];

            bool save = !isPresent(red, green, blue, redC, greenC, blueC, count);

            if (save) {
                blueC[count]  = blue;
                redC[count]   = red;
                greenC[count] = green;
                count++;
            }
        }
    }
    // for (int i = 0; i < count ; i++) {
    //     std::cout << (int)redC[i] << "," << (int)greenC[i] << "," << (int)blueC[i] << std::endl;
    // }
    std::cout << "Number of Unique colours : " << count << std::endl;
    return;
}

int main() {
    std::string image_path = "/home/arkadyuti/Pictures/asciiTable.png";
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    kotkota(img.clone(), cv::Scalar(255, 255, 255));
    playColors(img);
    namedWindow("Display window", WINDOW_NORMAL);
    resizeWindow("Display window", WIDTH, (int)((img.rows * WIDTH) / img.cols));
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's') {
        imwrite("AsciiTable.png", img);
    }
    return 0;
}