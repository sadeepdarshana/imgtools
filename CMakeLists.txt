

cmake_minimum_required(VERSION 3.12)
project(gilproj)

set(CMAKE_CXX_STANDARD 11)





add_executable(gilproj main.cpp)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(gilproj ${PNG_LIBRARY})