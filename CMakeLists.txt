cmake_minimum_required(VERSION 3.23)
project(Test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Eigen3)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(Test main.cpp)
target_link_libraries(Test ${OpenCV_LIBS} ${EIGEN3_LIBS})
