include(../CMakeHelper.cmake)
set(PROJ_NAME Editor)


target_apply_common_settings(${PROJ_NAME})

# Collect source and header files
collect_cpp_files("${CMAKE_CURRENT_SOURCE_DIR}/src")
collect_h_files("${CMAKE_CURRENT_SOURCE_DIR}/include")



include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_INCLUDE_PATH}")
include_vendors(${PROJ_NAME})

link_directories(${CMAKE_LIBRARY_PATH})

# Add executable
add_executable(${PROJ_NAME} ${SRC_FILES} ${INCLUDE_FILES})

# Link with Conan dependencies
target_link_libraries(${PROJ_NAME} ${STANDARD_LIBS})