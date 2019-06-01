cmake_minimum_required(VERSION 2.6)

# Name of project
project(Wolfenstein3D)

# Specify project files: header files and source files
file(GLOB SOURCES
    Source/Public/*.h
    Source/Private/*.cpp
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
    find_library(ASSIMP_LIB assimp)
	find_library(FREETYPE_LIB freetype)
    find_library(GLEW_LIB glew)
    find_library(SDL2_LIB SDL2)
    find_library(SFMLMAIN_LIB SFML)
    find_library(SFMLAUDIO_LIB SFML)
	find_library(SFMLSYSTEM_LIB)
    find_library(OPENAL_LIB SFML)
    find_library(PUGIXML_LIB SFML)
    find_library(FLAC_LIB SFML)
    find_library(VORBISENC_LIB SFML)
    find_library(VORBISFILE_LIB SFML)
    find_library(VORBIS_LIB SFML)
    find_library(OGG_LIB SFML)

elseif(WIN32)
    find_library(ASSIMP_LIB assimp HINTS ${LIBRARY_PATH}/lib/assimp)
    find_library(GLEW_LIB glew32 ${LIBRARY_PATH}/lib/glew)
    find_library(SDL2_LIB SDL2 HINTS ${LIBRARY_PATH}/lib/SDL2)
	find_library(FREETYPE_LIB freetyped HINTS ${LIBRARY_PATH}/lib/freetype)
    find_library(SFMLMAIN_LIB sfml-main-d HINTS ${LIBRARY_PATH}/lib/SFML)
    find_library(SFMLAUDIO_LIB sfml-audio-d HINTS ${LIBRARY_PATH}/lib/SFML)
	find_library(SFMLSYSTEM_LIB sfml-system-d HINTS ${LIBRARY_PATH}/lib/SFML)
    find_library(OPENAL_LIB openal32 HINTS ${LIBRARY_PATH}/lib/SFML)
    find_library(PUGIXML_LIB pugixml HINTS ${LIBRARY_PATH}/lib/pugixml)
    find_library(FLAC_LIB flac HINTS ${LIBRARY_PATH}/lib/SFML)
    find_library(VORBISENC_LIB vorbisenc HINTS ${LIBRARY_PATH}/lib/SFML)
    find_library(VORBISFILE_LIB vorbisfile HINTS ${LIBRARY_PATH}/lib/SFML)
    find_library(VORBIS_LIB vorbis HINTS ${LIBRARY_PATH}/lib/SFML)
    find_library(OGG_LIB ogg HINTS ${LIBRARY_PATH}/lib/SFML)
endif(NOT WIN32)

target_link_libraries(Wolfenstein3D ${ASSIMP_LIB})
target_link_libraries(Wolfenstein3D ${GLEW_LIB})
target_link_libraries(Wolfenstein3D ${SDL2_LIB})
target_link_libraries(Wolfenstein3D ${FREETYPE_LIB})
target_link_libraries(Wolfenstein3D ${SFMLMAIN_LIB})
target_link_libraries(Wolfenstein3D ${SFMLAUDIO_LIB})
target_link_libraries(Wolfenstein3D ${SFMLSYSTEM_LIB})
target_link_libraries(Wolfenstein3D ${OPENAL_LIB})
target_link_libraries(Wolfenstein3D ${PUGIXML_LIB})
target_link_libraries(Wolfenstein3D ${FLAC_LIB})
target_link_libraries(Wolfenstein3D ${VORBISENC_LIB})
target_link_libraries(Wolfenstein3D ${VORBISFILE_LIB})
target_link_libraries(Wolfenstein3D ${VORBIS_LIB})
target_link_libraries(Wolfenstein3D ${OGG_LIB})

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(Wolfenstein3D PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
