cmake_minimum_required(VERSION 2.8.1)
project(libphysics)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_definitions(-std=c++11)

find_package(Boost REQUIRED)
find_package(Box2D REQUIRED)
include_directories(. ${Boost_INCLUDE_DIRS})



add_subdirectory(physics)