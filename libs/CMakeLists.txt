cmake_minimum_required(VERSION 3.10)
project(libsodium C)

set(LIBSODIUM_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libsodium/src/libsodium")

if(NOT EXISTS "${LIBSODIUM_SRC_DIR}/include/sodium/version.h")
    file(WRITE "${LIBSODIUM_SRC_DIR}/include/sodium/version.h" 
        "#ifndef sodium_version_H\n#define sodium_version_H\n"
        "#define SODIUM_VERSION_STRING \"1.0.19\"\n"
        "#define SODIUM_LIBRARY_VERSION_MAJOR 26\n"
        "#define SODIUM_LIBRARY_VERSION_MINOR 1\n#endif\n")
endif()

file(GLOB_RECURSE SODIUM_SOURCES "${LIBSODIUM_SRC_DIR}/*.c")

if(NOT SODIUM_SOURCES)
    message(FATAL_ERROR "No source files found in: ${LIBSODIUM_SRC_DIR}")
endif()

add_library(sodium STATIC ${SODIUM_SOURCES})

# 3. Comprehensive Include Paths (Fixes core.h error)
target_include_directories(sodium PUBLIC 
    $<BUILD_INTERFACE:${LIBSODIUM_SRC_DIR}/include>
)
target_include_directories(sodium PRIVATE 
    ${LIBSODIUM_SRC_DIR}/include/sodium
    ${LIBSODIUM_SRC_DIR}/include/sodium/private
)

# 4. Suppress warnings and define environment
target_compile_definitions(sodium PRIVATE 
    SODIUM_DLL_EXPORT=1 
    CONFIGURED=1
    HAVE_ATOMIC_OPS=1
)

if(MSVC)
    target_compile_definitions(sodium PUBLIC SODIUM_STATIC=1)
endif()