  #-----------------------------------------------------------------------------#
  # Project
  cmake_minimum_required(VERSION 3.10)
  project(Simple)

  # Define variables
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")  # Add compiler flags

  #-----------------------------------------------------------------------------#

  # Find all source files
  file(GLOB_RECURSE CPP_FILES Simple/Src/*.cpp Src/*.cpp)

  # Add executable target
  add_executable(program ${CPP_FILES})

  # Include directories for the target "program"
  target_include_directories(program PRIVATE
      Simple/Include
      Simple/Include/matrices
      Simple/Include/Scene
      Simple/Include/Scene/Shapes
      Simple/Include/vectors
      Simple/Shaders
  )


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
      WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
  )

  # Add a custom target for cleaning
  add_custom_target(clean-all
      COMMAND ${CMAKE_COMMAND} -E remove program
      DEPENDS
      WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
  )

  #-----------------------------------------------------------------------------#