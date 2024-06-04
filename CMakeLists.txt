cmake_minimum_required(VERSION 3.28)
project(yygrams)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(yygrams main.cpp
        sdlui.cpp
        sdlui.h)

target_link_libraries(yygrams PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer)
