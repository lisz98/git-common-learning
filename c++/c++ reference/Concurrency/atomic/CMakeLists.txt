cmake_minimum_required(VERSION 3.0.0)
project(atomic_pro VERSION 0.1.0)

include(CTest)
enable_testing()

# 使用atomic_flag实现自旋互斥
add_executable(atomic_flag
atomic_flag.cc)

# 学习原子操作中的内存排序
add_executable(atomic_memory_order
atomic_memory_order.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
