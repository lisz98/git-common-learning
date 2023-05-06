set(BASE_SRCS
timestamp.cpp)

include_directories(./)

add_library(sz_base ${BASE_SRCS})

add_subdirectory(tests)