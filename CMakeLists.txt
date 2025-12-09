cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)

# set the project template
project(stpm)

# add internal dependencies
add_subdirectory(libs/googletest)
add_subdirectory(libs/libsodium)

# Recursively finds c++ source files
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()   

# Add and link executable with internal libraries
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs)
target_link_libraries(${PROJECT_NAME} PRIVATE sodium)

# add Unit tests
add_subdirectory(tests)