cmake_minimum_required(VERSION 3.5.0)
project(yo_window VERSION 1.0.0)

find_package(OpenGL REQUIRED)

add_executable(yo_window src/config.h src/main.cpp src/glad.c)

target_include_directories(yo_window PRIVATE ../_dependencies)
target_link_libraries(yo_window glfw3 OpenGL::GL)