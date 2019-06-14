cmake_minimum_required(VERSION 2.6)

# Name of project
project(Wolfenstein3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify project files: header files and source files
file(GLOB SOURCES
    Source/Public/*.h
    Source/Private/*.cpp
	Source/Private/*.c
)

# Add executable based on the source files
add_executable(Wolfenstein3D ${SOURCES})

# Require OpenGL library
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(Wolfenstein3D ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/Libraries/" CACHE PATH "Folder with GLEW, GLFW, GLM, ASSIMP, and SOIL libraries")
include_directories(${LIBRARY_PATH}/include
                    Source/Public)
if(NOT WIN32)
	find_library(FREETYPE_LIB freetype)
	find_library(IRRKLANG_LIB irrKlang)
	find_library(GLFW_LIB glfw3)
	find_library(ASSIMP_LIB assimp)

elseif(WIN32)
	find_library(FREETYPE_LIB freetyped HINTS ${LIBRARY_PATH}/lib/freetype)
	find_library(IRRKLANG_LIB irrKlang HINTS ${LIBRARY_PATH}/lib/irrKlang)
	find_library(GLFW_LIB glfw3 HINTS ${LIBRARY_PATH}/lib/GLFW)
	find_library(ASSIMP_LIB assimp HINTS ${LIBRARY_PATH}/lib/assimp)
endif(NOT WIN32)

target_link_libraries(Wolfenstein3D ${FREETYPE_LIB})
target_link_libraries(Wolfenstein3D ${IRRKLANG_LIB})
target_link_libraries(Wolfenstein3D ${GLFW_LIB})
target_link_libraries(Wolfenstein3D ${ASSIMP_LIB})

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(Wolfenstein3D PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
