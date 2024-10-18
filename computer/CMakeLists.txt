cmake_minimum_required(VERSION 3.14)
project(computer)

# Enable testing
enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        # GIT_TAG b514bdc898e2951020cbdca1304b75f5950d1f59#
        GIT_TAG origin/main
)

FetchContent_MakeAvailable(googletest)

# Verilator settings
find_package(verilator HINTS $ENV{VERILATOR_ROOT})

# List all test files
file(GLOB TEST_FILES "test/*_test.cpp")

# Lib files
include_directories(lib)
file(GLOB LIB_SOURCES "lib/*")

# Process each test file
foreach(TEST_FILE ${TEST_FILES})
    # Extract base name
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    string(REPLACE "_test" "" TEST_NAME ${TEST_NAME})
    # Corresponding SystemVerilog file
    file(GLOB SV_FILE "src/*/${TEST_NAME}.sv")
    file(GLOB SV_PACKAGES "src/packages/*.sv")

    if(${SV_FILE} MATCHES ".+src\/units\/.+$")
        file(GLOB SV_MODULES "src/modules/*.sv")
    else()
        set(SV_MODULES "")
    endif()


    # Create a target for each test

    set(VERILATED_DIR ${CMAKE_BINARY_DIR}/verilated_${TEST_NAME})

    add_executable(${TEST_NAME}_test ${TEST_FILE} ${LIB_SOURCES})

    # Verilate the SystemVerilog file and link it to the test executable
    verilate(${TEST_NAME}_test
            SOURCES ${SV_PACKAGES} ${SV_MODULES} ${SV_FILE}
            TOP_MODULE ${TEST_NAME}  # Specify the top module name
            PREFIX ${TEST_NAME}     # Prefix for Verilated files
            INCLUDE_DIRS "./src"  # Include directory for Verilog files
            TRACE_FST # Optional: Enable FST tracing
            COVERAGE
            DIRECTORY ${VERILATED_DIR}
            VERILATOR_ARGS --timing --timescale 1ps  # Additional Verilator arguments if needed
    )

    include_directories(lib ${VERILATED_DIR})



    # Link the Verilated model and Google Test libraries
    target_link_libraries(${TEST_NAME}_test PRIVATE
            GTest::gtest_main pthread)

    include(GoogleTest)
    gtest_discover_tests(${TEST_NAME}_test)
endforeach()
