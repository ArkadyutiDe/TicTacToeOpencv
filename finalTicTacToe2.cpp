#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#define __X 120 /* 120 is the ascii value of the key X */
#define __O 111 /* 111 is the ascii value of the key O */

struct TicTacToe{
    int position[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int size;
    int draw = __X;
    int winner = -1;
};

struct TicTacToe intializedGameState(int rows) {
    struct TicTacToe gameState;
    gameState.size = rows;
    return gameState;
}

int boardFullOrNot(int boardList[9]) {
    for (int i = 0; i < 9; i++) {
        if (boardList[i] == 0) {
            return 1;
        }
    }
    return -1;
}

int checkLine(int boardList[9]) {
    int line;

    if ( (boardList[0] == boardList[1]) && (boardList[1] == boardList[2]) && (boardList[0] != 0) ) line = 0;
    else if ( (boardList[3] == boardList[4]) && (boardList[4] == boardList[5]) && (boardList[3] != 0) ) line = 1;
    else if ( (boardList[6] == boardList[7]) && (boardList[7] == boardList[8]) && (boardList[6] != 0) ) line = 2;

    else if ( (boardList[0] == boardList[3]) && (boardList[3] == boardList[6]) && (boardList[0] != 0) ) line = 3;
    else if ( (boardList[1] == boardList[4]) && (boardList[4] == boardList[7]) && (boardList[1] != 0) ) line = 4;
    else if ( (boardList[2] == boardList[5]) && (boardList[5] == boardList[8]) && (boardList[2] != 0) ) line = 5;

    else if ( (boardList[0] == boardList[4]) && (boardList[4] == boardList[8]) && (boardList[0] != 0) ) line = 6;
    else if ( (boardList[2] == boardList[4]) && (boardList[4] == boardList[6]) && (boardList[2] != 0) ) line = 7;

    return line;
}

int checkWinner(int boardList[9]) {
    int winner;

    if ( (boardList[0] == boardList[1]) && (boardList[1] == boardList[2]) && (boardList[0] != 0) ) winner = boardList[0];
    else if ( (boardList[3] == boardList[4]) && (boardList[4] == boardList[5]) && (boardList[3] != 0) ) winner = boardList[3];
    else if ( (boardList[6] == boardList[7]) && (boardList[7] == boardList[8]) && (boardList[6] != 0) ) winner = boardList[6];

    else if ( (boardList[0] == boardList[3]) && (boardList[3] == boardList[6]) && (boardList[0] != 0) ) winner = boardList[0];
    else if ( (boardList[1] == boardList[4]) && (boardList[4] == boardList[7]) && (boardList[1] != 0) ) winner = boardList[1];
    else if ( (boardList[2] == boardList[5]) && (boardList[5] == boardList[8]) && (boardList[2] != 0) ) winner = boardList[2];

    else if ( (boardList[0] == boardList[4]) && (boardList[4] == boardList[8]) && (boardList[0] != 0) ) winner = boardList[0];
    else if ( (boardList[2] == boardList[4]) && (boardList[4] == boardList[6]) && (boardList[2] != 0) ) winner = boardList[2];

    return winner;
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
                if (gameState->position[move] == 0) {
                    gameState->position[move] = gameState->draw;
                }
                else{
                    if (gameState->draw == __O) {
                        gameState->draw = __X;
                    }
                    else if (gameState->draw == __X) {
                        gameState->draw = __O;
                    }
                }
            }
        }

        if (gameState->draw == __O) {
            gameState->draw = __X;
        }
        else if (gameState->draw == __X) {
            gameState->draw = __O;
        }
    }

}

void draw(cv::Mat image, int move, int row, int col, int size, cv::Scalar lineColour) {
    int r = 100;
    int font = cv::FONT_HERSHEY_SIMPLEX;
    double l1 = (size / 3), l2 = ((2 * size) / 3), start = 0, scale = 10, ls1 = start + (l1/2), ls2 = l1 + (l1/2), ls3 = l2 + (l1/2);
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

cv::Mat winningLine(cv::Mat image, int lineNumber, int size, cv::Scalar lineColour) {
    double l1 = (size / 3), l2 = ((2 * size) / 3), start = 0, scale = 10, ls1 = start + (l1/2), ls2 = l1 + (l1/2), ls3 = l2 + (l1/2);
    cv::Point2i pt1, pt2;
    float thickness = 7.5;

    if (lineNumber == 0) {
        pt1 = cv::Point2i(150, 0);
        pt2 = cv::Point2i(150, 900);
    }

    else if (lineNumber == 1) {
        pt1 = cv::Point2i(450, 0);
        pt2 = cv::Point2i(450, 900);
    }

    else if (lineNumber == 2) {
        pt1 = cv::Point2i(750, 0);
        pt2 = cv::Point2i(750, 900);
    }

    else if (lineNumber == 3) {
        pt1 = cv::Point2i(0, 150);
        pt2 = cv::Point2i(900, 150);
    }

    else if (lineNumber == 4) {
        pt1 = cv::Point2i(0, 450);
        pt2 = cv::Point2i(900, 450);
    }

    else if (lineNumber == 5) {
        pt1 = cv::Point2i(0, 750);
        pt2 = cv::Point2i(900, 750);
    }

    else if (lineNumber == 6) {
        pt1 = cv::Point2i(0, 0);
        pt2 = cv::Point2i(900, 900);
    }

    else if (lineNumber == 7) {
        pt1 = cv::Point2i(0, 900);
        pt2 = cv::Point2i(900, 0);
    }

    cv::line(image, pt1, pt2, lineColour, thickness);

    return image;
}

int main() {
    cv::Scalar backGround = cv::Scalar(255, 0, 0), lineColour = cv::Scalar(255, 255, 255);
    cv::Mat board = getBoard(900, backGround, lineColour), winnerShowingBoard(300, 900, CV_8UC3, backGround), board2;
    cv::Point2i point = cv::Point2i( ( ( (winnerShowingBoard.rows) / 3) ), ( ( 2 * (winnerShowingBoard.rows) / 3 )) );
    int font = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
    int key = -1, boardState = 1, line;
    float size = 3.5;

    struct TicTacToe gameState = intializedGameState(board.rows);

    cv::namedWindow("Board");
    cv::setMouseCallback("Board", CallBackTicTacToe, &gameState);

    while (key != 27 && boardState != -1) {
        board2 = drawOnBoard(gameState, board.clone(), lineColour);
        cv::imshow("Board", board2);
        gameState.winner = checkWinner(gameState.position);
        line = checkLine(gameState.position);
        boardState = boardFullOrNot(gameState.position);
        if (gameState.winner == __O || gameState.winner == __X || boardState == -1) {
            board2 = winningLine(board2, line, board2.rows, lineColour);
            break;
        }
        key = cv::waitKey(33);
    }

    if (gameState.winner == -1) cv::putText(winnerShowingBoard, "It's a draw...", point, font, size, lineColour);
    else if(gameState.winner == __X) cv::putText(winnerShowingBoard, "X is the winner...", point, font, size, lineColour);
    else if(gameState.winner == __O) cv::putText(winnerShowingBoard, "O is the winner...", point, font, size, lineColour);

    cv::imshow("Board", board2);

    cv::imshow("Result", winnerShowingBoard);
    cv::waitKey(0);

    return 0;
}