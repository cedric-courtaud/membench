cmake_minimum_required(VERSION 3.16)
project(membench)

set(CMAKE_CXX_STANDARD 14)



add_subdirectory(lib)
add_subdirectory(cmd)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()
