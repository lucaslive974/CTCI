cmake_minimum_required(VERSION 3.10.0)
project(CTCI VERSION 0.1.0 LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include("project_version")
include("language_standard")

file(GLOB_RECURSE CTCI_SOURCES "src/*.cpp")

add_executable(CTCI ${CTCI_SOURCES})
target_include_directories(CTCI PRIVATE "include")
