include(../CMakeHelper.cmake)
set(PROJ_NAME Engine)


target_apply_common_settings(${PROJ_NAME})

# Collect source and header files
collect_cpp_files("${CMAKE_CURRENT_SOURCE_DIR}/src")
collect_h_files("${CMAKE_CURRENT_SOURCE_DIR}/include")



include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_INCLUDE_PATH}")
include_vendors(${PROJ_NAME})

link_directories(${CMAKE_LIBRARY_PATH})

# Add the static library target
add_library(${PROJ_NAME} STATIC ${SRC_FILES} ${INCLUDE_FILES})

# Link with Conan dependencies
target_link_libraries(${PROJ_NAME} ${STANDARD_LIBS})