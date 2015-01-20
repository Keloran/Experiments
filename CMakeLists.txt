# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(Experiments)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -m64")

# Build Directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Build)

# Apple Boost
if (APPLE)
    link_directories(/usr/local/include)
    include_directories(/usr/local/include)
endif()

# Engine Options
option(NordicEngine_OSOnly "Setting OS Only OFF" OFF)
option(NordicEngine_UnitTests "Setting Unit Tests OFF" OFF)
option(NordicEngine_FullEngine "Setting Full Engine ON" ON)

option(ASSIMP_BUILD_ASSIMP_TOOLS "Settings AssImp Tools OFF" OFF)
option(ASSIMP_BUILD_SAMPLES "Settings AssImp Samples OFF" OFF)
option(ASSIMP_BUILD_TESTS "Setting AssImp Tests OFF" OFF)

option(GLFW_BUILD_EXAMPLES "Setting GLFW Examples OFF" OFF)
option(GLFW_BUILD_TESTS "Setting GLFW Tests OFF" OFF)
option(GLFW_BUILD_DOCS "Settings GLFW Docs OFF" OFF)

# Standard Include
include_directories(${PROJECT_SOURCE_DIR}/Experiments)

# Set Source
set(Ex ${PROJECT_SOURCE_DIR}/Experiments)
set(GameHeaders ${Ex}/Main.hpp)
set(GameSources ${Ex}/Main.cpp)

# Standard Includes
list(APPEND GameHeaders ${Ex}/Includes.hpp)

# NordicOS
link_directories(${Ex}/NordicEngine)
include_directories(${Ex}/NordicEngine)
add_subdirectory(${Ex}/NordicEngine)

# Boost
find_package(Boost COMPONENTS locale REQUIRED)
link_directories(${Boost_INCLUDES})
include_directories(${Boost_INCLUDES})

# Compile
add_executable(Experiments ${GameSources} ${GameHeaders})
set_target_properties(Experiments PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Experiments PROPERTIES OUTPUT_NAME "Experiments.app")

# Link
target_link_libraries(Experiments NordicEngine)
target_link_libraries(Experiments ${Boost_LIBRARIES})
