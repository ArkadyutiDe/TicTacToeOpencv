#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#define __X 120
#define __O 111

struct TicTacToe{
    int position[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int size;
    int draw = -1;
};

struct TicTacToe intializedGameState(int rows) {
    struct TicTacToe gameState;
    gameState.size = rows;
    return gameState;
}

cv::Mat getBoard(int size, cv::Scalar backgroundColour, cv::Scalar lineColour) {
    cv::Mat frame(size, size, CV_8UC3, backgroundColour);
    int thickness = 5;
    double l1 = (size / 3), l2 = ((2 * size) / 3), start = 0;
    cv::Point pt1 = cv::Point(start, l1), pt2 = cv::Point(size, l1);
    cv::line(frame, pt1, pt2,lineColour, thickness);
    cv::Point pt3 = cv::Point(start, l2), pt4 = cv::Point(size, l2);
    cv::line(frame, pt3, pt4,lineColour, thickness);
    cv::Point pt5 = cv::Point(l1, start), pt6 = cv::Point(l1, size);
    cv::line(frame, pt5, pt6,lineColour, thickness);
    cv::Point pt7 = cv::Point(l2, start), pt8 = cv::Point(l2, size);
    cv::line(frame, pt7, pt8,lineColour, thickness);
    return frame;
}

int positionMove(int x, int y, int size, int l1, int l2) {
    int move;
    if (x < l1) {
        if (y < l1) {
            move = 0;
        }
        else {
            if (y < l2) {
                move = 1;
            }
            else {
                move = 2;
            }
        }
    }
    else if (x < l2) {
        if (y < l1) {
            move = 3;
        }
        else {
            if (y < l2) {
                move = 4;
            }
            else {
                move = 5;
            }
        }
    }
    else if (x < size) {
        if (y < l1) {
            move = 6;
        }
        else {
            if (y < l2) {
                move = 7;
            }
            else {
                move = 8;
            }
        }
    }
    else{
        move = -1;
    }

    return move;
}

void CallBackTicTacToe(int event, int x, int y , int flags, void * list) {
    int move;
    struct TicTacToe * gameState = (struct TicTacToe*)list;
    double l1 = (gameState->size / 3), l2 = ((2 * gameState->size) / 3), start = 0;

    if (event == cv::EVENT_LBUTTONUP) {
        move = positionMove(x, y, gameState->size, l1, l2);

        if (move != -1) {
            if (gameState->draw == __O || gameState->draw == __X) {
                gameState->position[move] = gameState->draw;
            }
        }
    }

}

void draw(cv::Mat image, int move, int row, int col, int size, cv::Scalar lineColour) {
    int r = 100;
    int font = cv::FONT_HERSHEY_SIMPLEX;
    double l1 = (size / 3);
    double l2 = ((2 * size) / 3);
    double start = 0;
    double scale = 10;
    double ls1 = start + (l1/2);
    double ls2 = l1 + (l1/2);
    double ls3 = l2 + (l1/2);
    cv::Point2i pt;

    if (row == 0)row = ls1 - r;
    else if (row == 1)row = ls2 - r;
    else if (row == 2)row = ls3 - r;

    if (col == 0)col = ls1 + r;
    else if (col == 1)col = ls2 + r;
    else if (col == 2)col = ls3 + r;

    pt = cv::Point2i(row, col);

    if (move == __O) {
        cv::putText(image, "0", pt, font, scale, lineColour);
    }

    else if (move == __X) {
        cv::putText(image, "X", pt, font, scale, lineColour);
    }

    return;
}


cv::Mat drawOnBoard(TicTacToe myThings, cv::Mat image, cv::Scalar lineColour) {
    for(int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;
        int move = myThings.position[i];
        draw(image, move, row, col, myThings.size, lineColour);
    }

    return image;
}

int main() {
    cv::Scalar backGround = cv::Scalar(255, 0, 0), lineColour = cv::Scalar(255, 255, 255);
    cv::Mat board = getBoard(900, backGround, lineColour);
    int key = -1;

    struct TicTacToe gameState = intializedGameState(board.rows);

    cv::namedWindow("Board");
    cv::setMouseCallback("Board", CallBackTicTacToe, &gameState);

    while (key != 27) {
        cv::Mat board2 = drawOnBoard(gameState, board.clone(), lineColour);
        cv::imshow("Board", board2);
        key = cv::waitKey(33);
        if (key != -1) gameState.draw = key;
    }

    return 0;
}