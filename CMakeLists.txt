cmake_minimum_required(VERSION 3.0)
project(Simple)

# Add include directories
include_directories(Include Shaders)

# Add source files
file(GLOB SOURCES "Src/*.cpp" "Src/Shapes/*.cpp")

# Add executable target
add_executable(simple ${SOURCES})

# Link libraries
target_link_libraries(simple glew32 opengl32 glfw3dll freeglut glu32)

