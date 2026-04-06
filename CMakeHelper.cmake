SET(STANDARD_LIBS ZLIB::ZLIB spdlog::spdlog OpenAL::OpenAL sdl::sdl vulkan-headers::vulkan-headers boost::boost)

# Function to collect .cpp files in the src directory
function(collect_cpp_files DIR OUT_VAR)
    file(GLOB_RECURSE CPP_FILES
            CONFIGURE_DEPENDS
            "${DIR}/*.cpp"
            "${DIR}/*.c"
    )
    set(${OUT_VAR} ${CPP_FILES} PARENT_SCOPE)
endfunction()

function(collect_h_files DIR OUT_VAR)
    file(GLOB_RECURSE H_FILES
            CONFIGURE_DEPENDS
            "${DIR}/*.h"
            "${DIR}/*.hpp"
    )
    set(${OUT_VAR} ${H_FILES} PARENT_SCOPE)
endfunction()


function(include_vendors TARGET_NAME)
    target_include_directories(${TARGET_NAME}
            PRIVATE
            "${CMAKE_SOURCE_DIR}/vendors/bgfx/include"
            "${CMAKE_SOURCE_DIR}/vendors/physx/physx/include"
            "${CMAKE_SOURCE_DIR}/vendors/ShaderConductor/Include"
            "${CMAKE_SOURCE_DIR}/vendors/stb"
            "${CMAKE_SOURCE_DIR}/vendors/assimp/include"
    )
endfunction()

function(add_cmake_vendors)
    add_subdirectory("${CMAKE_SOURCE_DIR}/vendors/assimp")
    add_subdirectory("${CMAKE_SOURCE_DIR}/vendors/ShaderConductor")
endfunction()

function(target_apply_common_settings TARGET_NAME)
    target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)

    if (MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE /Zc:__cplusplus /W4 /permissive-)
    else()
        target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()