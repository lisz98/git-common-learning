cmake_minimum_required(VERSION 3.0.0)
project(thread VERSION 0.1.0)

include(CTest)
enable_testing()


# ! 浠ヤ笅瀛︿範鍐呭寮曠敤鑷綉绔� cppreference.com


# # c++ 璇█鐗规€�?
# add_subdirectory(Language)

# # c++ 鍐呭瓨绠＄悊
add_subdirectory(Memory)

# # c++ 鍏冪紪绋嬪簱
# add_subdirectory(Metaprogramming)

# # c++ 閫氱敤宸ュ叿搴�
add_subdirectory(General)

# # c++ 瀛楃涓插簱
# add_subdirectory(String)

# # c++ 瀹瑰櫒搴�?
# add_subdirectory(Containers)

# # c++ 杩唬鍣ㄥ簱
# add_subdirectory(Iterators)

# # c++ IO搴�
# add_subdirectory(IO)

# # c++ 姝ｅ垯琛ㄨ揪寮忓�?
# add_subdirectory(Regex)

# c++11 骞跺彂缂栫▼
add_subdirectory(Concurrency)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
