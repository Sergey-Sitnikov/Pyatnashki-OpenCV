cmake_minimum_required(VERSION 3.11)
project(web)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/include/X11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/home/ssv/libraries_cpp")
find_package(OpenCV REQUIRED)
find_package(X11 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(web src/main.cpp src/pytnashki.h src/pytnashki.cpp)
#target_link_libraries(web ${X11_LIBRARIES})

target_link_libraries(web ${OpenCV_LIBS} ${X11_LIBRARIES})