cmake_minimum_required(VERSION 3.0.0)
project(mutex_pro VERSION 0.1.0)

include(CTest)
enable_testing()

# 使用Mutex
add_executable(test_mutex
test_mutex.h
test_mutex.cc)

# 使用 timed_mutex
add_executable(test_timed_mutex
test_timed_mutex.cc)

# 使用 recursive_mutex
add_executable(test_recursive_mutex
test_recursive_mutex.cc)

# 使用 recursive_timed_mutex
add_executable(test_recursive_timed_mutex
test_recursive_timed_mutex.cc)

# 使用 call_once 函数
add_executable(test_call_once
test_call_once.cc)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
