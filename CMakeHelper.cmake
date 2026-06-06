SET(STANDARD_LIBS ZLIB::ZLIB fmt::fmt spdlog::spdlog OpenAL::OpenAL sdl::sdl vulkan-headers::vulkan-headers boost::boost bgfx::bgfx)

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

function(set_target_output_dirs target)
    if(CMAKE_CONFIGURATION_TYPES)
        foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
            string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)

            get_target_property(TARGET_TYPE ${target} TYPE)

            if(TARGET_TYPE STREQUAL "EXECUTABLE")
                set_target_properties(${target} PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER}
                        "${CMAKE_BINARY_DIR}/build/bin/${OUTPUTCONFIG}/${target}"
                )
            else()
                set_target_properties(${target} PROPERTIES
                        RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER}
                        "${CMAKE_BINARY_DIR}/build/lib/${OUTPUTCONFIG}/${target}"
                        LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER}
                        "${CMAKE_BINARY_DIR}/build/lib/${OUTPUTCONFIG}/${target}"
                        ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER}
                        "${CMAKE_BINARY_DIR}/build/lib/${OUTPUTCONFIG}/${target}"
                )
            endif()
        endforeach()
    else()
        get_target_property(TARGET_TYPE ${target} TYPE)

        if(TARGET_TYPE STREQUAL "EXECUTABLE")
            set_target_properties(${target} PROPERTIES
                    RUNTIME_OUTPUT_DIRECTORY
                    "${CMAKE_BINARY_DIR}/build/bin/${target}"
            )
        else()
            set_target_properties(${target} PROPERTIES
                    RUNTIME_OUTPUT_DIRECTORY
                    "${CMAKE_BINARY_DIR}/build/lib/${target}"
                    LIBRARY_OUTPUT_DIRECTORY
                    "${CMAKE_BINARY_DIR}/build/lib/${target}"
                    ARCHIVE_OUTPUT_DIRECTORY
                    "${CMAKE_BINARY_DIR}/build/lib/${target}"
            )
        endif()
    endif()
endfunction()


function(copy_runtime_deps target)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${target}>
            $<TARGET_FILE_DIR:${target}>
            COMMAND_EXPAND_LISTS
    )
endfunction()