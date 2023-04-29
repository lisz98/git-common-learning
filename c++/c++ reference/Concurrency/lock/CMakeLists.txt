cmake_minimum_required(VERSION 3.0.0)
project(condition_pro VERSION 0.1.0)

include(CTest)
enable_testing()

# ѧϰ lock_guard
add_executable(lock_guard
lock_guard.cc)

add_executable(unique_lock
unique_lock.cc)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
