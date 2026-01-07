cmake_minimum_required(VERSION 3.12.0)
project(yo_window VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)


set(CMAKE_CXX_STANDARD 20)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif(CMAKE_COMPILER_IS_GNUCXX)

find_package(OpenGL REQUIRED)

add_subdirectory(_dependencies/glfw EXCLUDE_FROM_ALL)
# add_subdirectory(_dependencies/glm EXCLUDE_FROM_ALL)

add_executable(yo_window
    src/main.cpp
    src/glad.c
    
    src/factories/factory.cpp
    src/factories/texture_factory.cpp

    src/systems/camera_system.cpp
    src/systems/render_system.cpp

    src/view/shader.cpp
    src/controller/app.cpp
)

target_include_directories(yo_window
    PRIVATE
    _dependencies
)
target_link_libraries(yo_window
    glfw3
    OpenGL::GL
)