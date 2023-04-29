cmake_minimum_required(VERSION 3.0.0)
project(thread VERSION 0.1.0)

include(CTest)
enable_testing()


# ! 以下学习内容引用自网站 cppreference.com


# # c++ 语言特性
# add_subdirectory(Language)

# # c++ 内存管理
# add_subdirectory(Memory)

# # c++ 元编程库
# add_subdirectory(Metaprogramming)

# # c++ 通用工具库
# add_subdirectory(General)

# # c++ 字符串库
# add_subdirectory(String)

# # c++ 容器库
# add_subdirectory(Containers)

# # c++ 迭代器库
# add_subdirectory(Iterators)

# # c++ IO库
# add_subdirectory(IO)

# # c++ 正则表达式库
# add_subdirectory(Regex)

# c++11 并发编程
add_subdirectory(Concurrency)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
