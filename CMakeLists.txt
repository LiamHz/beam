cmake_minimum_required(VERSION 3.17.0)

project(beam)
include_directories(${CMAKE_SOURCE_DIR})

# Create scenes directory
file(MAKE_DIRECTORY scenes)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory scenes)

# Copy all .scene files into directory
# file(GLOB SCENE_FILES "${CMAKE_SOURCE_DIR}/scenes/*.scene")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scenes/default.scene ${CMAKE_CURRENT_BINARY_DIR}/scenes/ COPYONLY)
file(COPY ${SCENE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/scenes/)

set(CMAKE_CXX_STANDARD 11)
add_executable(main core/main.cpp core/integrator.cpp core/scene.cpp integrators/whitted.cpp shapes/sphere.cpp)
