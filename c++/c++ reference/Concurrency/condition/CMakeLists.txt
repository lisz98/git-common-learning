cmake_minimum_required(VERSION 3.0.0)
project(condition_pro VERSION 0.1.0)

include(CTest)
enable_testing()

# 学习条件变量 condition_variable 使用
add_executable(condition_variable
condition_variable.cc)

add_executable(condition_variable_any
condition_variable_any.cc)

add_executable(notify_all_at_thread_exit
notify_all_at_thread_exit.cc)

add_executable(semaphore
semaphore.cc)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
