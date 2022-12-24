cmake_minimum_required(VERSION 3.18)
project(ledControl)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/include/ws2811")

add_executable(ledControl main.c driver.c driver.h service.h service.c)
target_link_libraries(ledControl libws2811.so pthread)
