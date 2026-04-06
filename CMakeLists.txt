cmake_minimum_required(VERSION 3.26)
project(SoullessEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(spdlog REQUIRED)
find_package(ZLIB REQUIRED)


# Your engine
add_subdirectory(engine)

add_subdirectory(editor)