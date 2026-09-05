cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

set(ABSL_ENABLE_INSTALL ON CACHE BOOL "" FORCE)
set(RE2_BUILD_TESTING OFF CACHE BOOL "" FORCE)

# set the project template
project(stpm VERSION 0.1.0 LANGUAGES CXX)


configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/version.h"
)

# add internal dependencies
add_subdirectory(libs/googletest)
add_subdirectory(libs/abseil-cpp)
add_subdirectory(libs/re2)
add_subdirectory(libs/FTXUI)
add_subdirectory(libs/clipboard)
add_subdirectory(libs) # for those libs which doesn't have CMakeLists.txt file

# Recursively finds c++ source files
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()   

# Add and link executable with internal libraries
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated)
target_link_libraries(${PROJECT_NAME} PRIVATE sodium re2 absl::base ftxui::ftxui clip)
target_compile_options(${PROJECT_NAME} PRIVATE 
    $<$<CONFIG:Release>:-Ofast>
)
# add Unit tests
add_subdirectory(tests)