cmake_minimum_required(VERSION 3.5.0)
project(yo_window VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

find_package(Git QUIET)
if (EXISTS "${PROJECT_SOURCE_DIR/.git}")
    option(GIT_SUBMODULE "Check submodules during build!" ON)
    if (GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${git_executable} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please check out submodule.")
        endif()
    endif()
endif()


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
    src/config.h
    src/config.cpp
    src/main.cpp
    src/glad.c
    src/factories/factory.cpp
    src/factories/mesh_factory.cpp
    src/systems/camera_system.cpp
    src/systems/motion_system.cpp
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