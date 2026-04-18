# this CMakeLists.txt file is used for projects not having a CMakeLists.txt file

cmake_minimum_required(VERSION 3.10)
project(libsodium C)

# 2. Add all relevant source files (simplified example)
# Note: For a production build, you should list the specific 
# source files required for your target architecture.
file(GLOB_RECURSE SODIUM_SOURCES "libsodium/src/libsodium/*.c")

# 3. Create the library
add_library(sodium ${SODIUM_SOURCES})

# 4. Set include directories so your main project can find the headers
target_include_directories(sodium PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/libsodium/src/libsodium/include/sodium
)

# 5. Handle platform-specific defines
if(MSVC)
    target_compile_definitions(sodium PRIVATE SODIUM_STATIC=1 SODIUM_EXPORT=)
else()
    target_compile_definitions(sodium PRIVATE HAVE_ATOMIC_OPS=1)
endif()