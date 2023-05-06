cmake_minimum_required(VERSION 3.0.0)
project(new_pro VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(new
new.cc)

add_executable(unique_ptr
unique_ptr.cc)

add_executable(shared_ptr
shared_ptr.cc)

add_executable(weak_ptr
weak_ptr.cc)

add_executable(enable_shared_from_this
enable_shared_from_this.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
