include(../CMakeHelper.cmake)
set(PROJ_NAME engine)

# Collect source and header files
collect_cpp_files("${CMAKE_CURRENT_SOURCE_DIR}/src" SRC_FILES)
collect_h_files("${CMAKE_CURRENT_SOURCE_DIR}/include" INCLUDE_FILES)

# Add the static library target
add_library(${PROJ_NAME} STATIC ${SRC_FILES} ${INCLUDE_FILES})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_INCLUDE_PATH}")

link_directories(${CMAKE_LIBRARY_PATH})

target_apply_common_settings(${PROJ_NAME})
include_vendors(${PROJ_NAME})

target_precompile_headers(${PROJ_NAME}
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/soulless/${PROJ_NAME}/pch.hpp"
)

# Link with Conan dependencies
target_link_libraries(${PROJ_NAME} ${STANDARD_LIBS})