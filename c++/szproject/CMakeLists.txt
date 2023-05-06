cmake_minimum_required(VERSION 3.0)

project(szproject)

set(CMAKE_CXX_FLAGS
    "-g -Wall -rdynamic"
)

include_directories(${PEOJECT_SOURCE_DIR})
add_subdirectory(base)