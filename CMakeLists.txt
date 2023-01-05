cmake_minimum_required(VERSION 3.11)
project(web)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(web src/main.cpp src/pytnashki.h src/pytnashki.cpp)
target_link_libraries(web ${OpenCV_LIBS})
