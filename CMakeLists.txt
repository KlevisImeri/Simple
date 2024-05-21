#-----------------------------------------------------------------------------#
# Project
cmake_minimum_required(VERSION 3.10)
project(Simple)

# Define variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")  # Add compiler flags

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Additional flags for different build types
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

#-----------------------------------------------------------------------------#

# Find all source files
file(GLOB_RECURSE CPP_FILES "${CMAKE_SOURCE_DIR}/Simple/Src/*.cpp" "${CMAKE_SOURCE_DIR}/Src/*.cpp")

# Find all header files
file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/Simple/Include/*.h")

# Extract unique directories from header files
set(INCLUDE_DIRS "")
foreach(_headerFile ${HEADER_FILES})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# Include directories
include_directories(${INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Add executable target
add_executable(program ${CPP_FILES})

# Copy texture files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Src/brickwall.bmp ${CMAKE_CURRENT_BINARY_DIR}/brickwall.bmp COPYONLY)

# Link libraries based on platform
if(UNIX)
    find_package(OpenGL REQUIRED)
    set(LIBS ${OPENGL_LIBRARIES} GLEW glfw glut GLU)
else()
    set(LIBS glew32 opengl32 glfw3dll freeglut glu32)
endif()
target_link_libraries(program ${LIBS})

#-----------------------------------------------------------------------------#

# Add a custom target for running the program
add_custom_target(run
    COMMAND program
    DEPENDS program
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# Add a custom target for cleaning
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove program
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(debug
    COMMAND gdb -ex=r --args program
    DEPENDS program
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

#-----------------------------------------------------------------------------#
