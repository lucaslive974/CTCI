list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include("gtest")

file(GLOB_RECURSE CTCI_TEST_SOURCE "tests/*.cpp")
enable_testing()

add_executable(CTCI_TEST ${CTCI_TEST_SOURCE})
target_include_directories(CTCI_TEST PRIVATE "include")
target_link_libraries(CTCI_TEST CTCI GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(CTCI_TEST)

