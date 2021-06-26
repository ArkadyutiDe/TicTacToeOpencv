cmake_minimum_required(VERSION 3.6)
project(PixelManipualtion)

set(OpenCV_DIR "//home/arkadyuti/Documents/externalLibrary/opencv/install/lib/cmake/opencv4")

# set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${OpenCV_DIR}")
# message(">>>" ${CMAKE_MODULE_PATH})
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(BasicDrawing basicDrawing.cpp)
target_link_libraries(BasicDrawing ${OpenCV_LIBS})

add_executable(KeyboardUserInput keyboardInput.cpp)
target_link_libraries(KeyboardUserInput ${OpenCV_LIBS})

add_executable(MouseInput mouseInput.cpp)
target_link_libraries(MouseInput ${OpenCV_LIBS})

add_executable(TTTShow ticTacToeShow.cpp)
target_link_libraries(TTTShow ${OpenCV_LIBS})

add_executable(TicTacToe ticTacToe.cpp)
target_link_libraries(TicTacToe ${OpenCV_LIBS})

add_executable(TicTacToe2 ticTacToe2.cpp)
target_link_libraries(TicTacToe2 ${OpenCV_LIBS})

add_executable(TicTacToe3 ticTacToe3.cpp)
target_link_libraries(TicTacToe3 ${OpenCV_LIBS})

add_executable(FinalTicTacToe finalTicTacToe.cpp)
target_link_libraries(FinalTicTacToe ${OpenCV_LIBS})

add_executable(FinalTicTacToe2 finalTicTacToe2.cpp)
target_link_libraries(FinalTicTacToe2 ${OpenCV_LIBS})

add_executable(ShowTTT ticTacToeShow2.cpp)
target_link_libraries(ShowTTT ${OpenCV_LIBS})

add_executable(PixelManipualtion pixelManipulation.cpp)
target_link_libraries(PixelManipualtion ${OpenCV_LIBS})
