cmake_minimum_required(VERSION 3.26)
project(SoullessEngine)

include(CMakeHelper.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
    add_compile_options(/utf-8)
endif()

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenAL REQUIRED)
find_package(SDL3 REQUIRED)
find_package(VulkanHeaders REQUIRED)
find_package(boost REQUIRED)


add_subdirectory(engine)

add_subdirectory(editor)

add_subdirectory(launcher)