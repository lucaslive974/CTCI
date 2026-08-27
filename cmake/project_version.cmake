if(NOT CMAKE_BUILD_TYPE)
set(default_build_type "Debug")
message(STATUS "Set the build type to ${default_build_type} as nona was specified")
set(CMAKE_BUILD_TYPE ${default_build_type} CACHE STRING "Choose the build type." FORCE)
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRING "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message(STATUS "CTCI Build Type: ${CMAKE_BUILD_TYPE}")

set(CTCI_VERSION_MAJOR 0)
set(CTCI_VERSION_MINOR 1)
set(CTCI_VERSION_PATCH 0)
set(CTCI_VERSION_STATUS "dev")
set(PROJECT_VERSION
    "${CTCI_VERSION_MAJOR}.${CTCI_VERSION_MINOR}.${CTCI_VERSION_PATCH}-${CTCI_VERSION_STATUS}"
)

message(STATUS "${PROJECT_NAME} version: ${PROJECT_VERSION}")
