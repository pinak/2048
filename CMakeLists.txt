cmake_minimum_required(VERSION 2.8.12)

project(2048)

find_package(Qt5 COMPONENTS Quick Core)
set(CMAKE_AUTOMOC ON)

include_directories($CMAKE_SOURCE_DIR/src)

add_subdirectory(src)