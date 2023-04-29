cmake_minimum_required(VERSION 3.0.0)
project(thread_pro VERSION 0.1.0)

include(CTest)
enable_testing()


# message(DEBUG  "${CMAKE_CURRENT_SOURCE_DIR}")

# thread 类
add_executable(test_thread
thread/test_thread.h
thread/test_thread.cpp)

# jthread 类 c++ 20新特性
add_executable(test_jthread
jthread/test_jthread.h
jthread/test_jthread.cpp)

# 原子锁操作
add_subdirectory(atomic)

# mutex
add_subdirectory(mutex)

# 互斥锁管理
add_subdirectory(lock)

# 条件变量
add_subdirectory(condition)

# 异步执行任务
add_subdirectory(future)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
