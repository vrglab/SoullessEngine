SET(STANDARD_LIBS ZLIB::ZLIB spdlog::spdlog)

# Function to collect .cpp files in the src directory
function(collect_cpp_files DIR)
    file(GLOB_RECURSE CPP_FILES "${DIR}/*.cpp" "${DIR}/*.c")
    set(SRC_FILES ${CPP_FILES} PARENT_SCOPE)
endfunction()

# Function to collect .h files in the include directory
function(collect_h_files DIR)
    file(GLOB_RECURSE H_FILES "${DIR}/*.h" "${DIR}/*.hpp" "${DIR}/**/*.h" "${DIR}/**/*.hpp")
    set(INCLUDE_FILES ${H_FILES} PARENT_SCOPE)
endfunction()


function(include_vendors TARGET_NAME)
    target_include_directories(${TARGET_NAME}
            PRIVATE
            "${CMAKE_SOURCE_DIR}/vendors/bgfx/include"
            "${CMAKE_SOURCE_DIR}/vendors/physx/physx/include"
            "${CMAKE_SOURCE_DIR}/vendors/ShaderConductor/Include"
            "${CMAKE_SOURCE_DIR}/vendors/stb"
    )
endfunction()

function(target_apply_common_settings TARGET_NAME)
    target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)

    if (MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE /Zc:__cplusplus /W4 /permissive-)
    else()
        target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()