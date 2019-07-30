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
target_link_libraries(Wolfenstein3D PRIVATE ${OPENGL_gl_LIBRARY})

find_package(folly CONFIG REQUIRED)
target_link_libraries(Wolfenstein3D PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)

find_package(glm CONFIG REQUIRED)
target_link_libraries(Wolfenstein3D PRIVATE glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(Wolfenstein3D PRIVATE glfw)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Wolfenstein3D PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

find_package(Freetype REQUIRED)
target_link_libraries(Wolfenstein3D PRIVATE Freetype::Freetype)

find_package(assimp REQUIRED)
target_link_libraries(Wolfenstein3D PRIVATE assimp)

find_package(glad CONFIG REQUIRED)
target_link_libraries(Wolfenstein3D PRIVATE glad::glad)


# Other libraries needed
set(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/Libraries/" CACHE PATH "Folder with GLEW, GLFW, GLM, ASSIMP, and SOIL libraries")
include_directories(${LIBRARY_PATH}/include
                    Source/Public)
if(NOT WIN32)
	find_library(IRRKLANG_LIB irrKlang)

elseif(WIN32)
	find_library(IRRKLANG_LIB irrKlang HINTS ${LIBRARY_PATH}/lib/irrKlang)
endif(NOT WIN32)

target_link_libraries(Wolfenstein3D PRIVATE ${IRRKLANG_LIB})

# Avoid ZERO_CHECK target in Visual Studio
set(CMAKE_SUPPRESS_REGENERATION TRUE)

# This will use the proper libraries in debug mode in Visual Studio
set_target_properties(Wolfenstein3D PROPERTIES DEBUG_POSTFIX _d)
