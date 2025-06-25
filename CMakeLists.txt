cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(BUILD_SHARED_LIBS OFF)

# set the project template
project(template)

# add internal dependencies
add_subdirectory(libs/fmt)
add_subdirectory(libs/googletest)

# Recursively finds c++ source files
file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")

# Add and link executable with internal libraries
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt)

# add Unit tests
add_subdirectory(tests)