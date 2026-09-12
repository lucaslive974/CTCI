cmake_minimum_required(VERSION 3.10.0)
project(CTCI VERSION 0.1.0 LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include("utils")
include("project_version")
include("language_standard")

file(GLOB_RECURSE CTCI_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_library(CTCI ${CTCI_SOURCES})
target_include_directories(CTCI PRIVATE "include")

# Linter and Formatter
find_program(LINTER_TOOL NAMES run-clang-tidy)

if(LINTER_TOOL)
    cmake_host_system_information(RESULT NPROC QUERY NUMBER_OF_LOGICAL_CORES)

    set(LINTER_NTHREADS "${NPROC}" CACHE STRING "Number of linter threads")
    set(CLANG_TIDY_SOURCE_FILTER [=[".*CTCI\/src|include|tests.*\.cpp|hpp$$"]=] CACHE STRING "" FORCE)

    add_custom_target(lint-and-format
        COMMAND ${LINTER_TOOL}
        -fix
        -format
        -quiet
        -j "${LINTER_NTHREADS}"
        -p "${CMAKE_BINARY_DIR}"
        "-source-filter=${CLANG_TIDY_SOURCE_FILTER}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Running Clang-Tidy with autofix and autoformat..."
    )
endif()

include(tests)