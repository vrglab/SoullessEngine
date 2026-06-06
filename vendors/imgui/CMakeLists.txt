include(../../CMakeHelper.cmake)
set(PROJ_NAME imgui)


# Collect source and header files
collect_cpp_files("${CMAKE_CURRENT_SOURCE_DIR}/backends" SRC_FILES)
collect_h_files("${CMAKE_CURRENT_SOURCE_DIR}" INCLUDE_FILES)


# Add executable
add_library(${PROJ_NAME} STATIC ${SRC_FILES} ${INCLUDE_FILES})


target_include_directories(${PROJ_NAME}
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

link_directories(${CMAKE_LIBRARY_PATH})

target_apply_common_settings(${PROJ_NAME})


# Link with Conan dependencies
target_link_libraries(${PROJ_NAME} ${STANDARD_LIBS})

set_target_output_dirs(${PROJ_NAME})