list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CTest)
include("gtest")

file(GLOB_RECURSE CTCI_TEST_SOURCE CONFIGURE_DEPENDS "tests/*.cpp")

add_executable(CTCI_TEST ${CTCI_TEST_SOURCE})
option(ENABLE_COVERAGE "Enable code coverage instrumentation" OFF)

if(ENABLE_COVERAGE)
    target_link_libraries(CTCI_TEST PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,CTCI>" GTest::gtest_main)
    enable_coverage_instrumentation(CTCI)
else()
    target_link_libraries(CTCI_TEST PRIVATE CTCI GTest::gtest_main)
endif()

include(GoogleTest)
gtest_discover_tests(CTCI_TEST
    PROPERTIES ENVIRONMENT "LLVM_PROFILE_FILE=${CMAKE_BINARY_DIR}/coverage_%p.profraw"
)

# --- Coverage Target Generation ---
set(COVERAGE_REPORT_DIR "${CMAKE_BINARY_DIR}/coverage" CACHE STRING "" FORCE)
set(COVERAGE_PROFDATA "${CMAKE_BINARY_DIR}/coverage.profdata" CACHE STRING "" FORCE)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Resolve version-matched or generic LLVM tools
    find_program(LLVM_PROFDATA_TOOL NAMES llvm-profdata llvm-profdata-${CMAKE_CXX_COMPILER_VERSION})
    find_program(LLVM_COV_TOOL NAMES llvm-cov llvm-cov-${CMAKE_CXX_COMPILER_VERSION})

    if(LLVM_PROFDATA_TOOL AND LLVM_COV_TOOL)
        set(INSTR_PROFILE "-instr-profile=${COVERAGE_PROFDATA}" CACHE STRING "Instrumentation profile" FORCE)
        set(IGNORE_TEST_RE [=[--ignore-filename-regex=tests/\|.*_deps.*]=] CACHE STRING "" FORCE)

        add_custom_target(generate-coverage-report
            COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_BINARY_DIR}/*.profraw ${COVERAGE_PROFDATA}

            COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure

            COMMAND
            ${LLVM_PROFDATA_TOOL} merge -sparse
            ${CMAKE_BINARY_DIR}/*.profraw
            -o ${CMAKE_BINARY_DIR}/coverage.profdata

            COMMAND
            ${LLVM_COV_TOOL} export $<TARGET_FILE:CTCI_TEST>
            ${INSTR_PROFILE}
            ${IGNORE_TEST_RE}
            -format=lcov
            > ${CMAKE_BINARY_DIR}/lcov.info

            COMMAND
            ${LLVM_COV_TOOL} report $<TARGET_FILE:CTCI_TEST>
            ${INSTR_PROFILE}
            ${IGNORE_TEST_RE}
            -format=text

            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS CTCI_TEST
            COMMENT "Generating LLVM coverage report..."
        )
    endif()

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    find_program(LCOV_TOOL lcov)
    find_program(GENHTML_TOOL genhtml)

    if(LCOV_TOOL AND GENHTML_TOOL)
        add_custom_target(generate-coverage-report
            COMMAND ${LCOV_TOOL} --directory ${CMAKE_BINARY_DIR} --zerocounters
            COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure

            # Capture gcov tracefile from build directory
            COMMAND ${LCOV_TOOL} --directory ${CMAKE_BINARY_DIR} --capture --output-file ${CMAKE_BINARY_DIR}/coverage.info

            # Filter out external, system headers, tests, and third-party dependencies
            COMMAND ${LCOV_TOOL} --remove ${CMAKE_BINARY_DIR}/coverage.info '/usr/*' '*/tests/*' '*/_deps/*' --output-file ${CMAKE_BINARY_DIR}/lcov.info

            # Generate HTML dashboard
            COMMAND ${GENHTML_TOOL} ${CMAKE_BINARY_DIR}/lcov.info --output-directory ${COVERAGE_REPORT_DIR}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS CTCI_TEST
            COMMENT "Generating GCC/gcov coverage report with lcov..."
        )
    endif()
endif()