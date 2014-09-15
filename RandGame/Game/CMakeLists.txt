# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(GameLibrary)

# Module Finder Path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../CMakeModules/")

# Output Dir
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../Build/Lib)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 --stdlib=libc++ -m64")
set(EXTRA_FLAGS " -x objective-c++")

# Directories
set(GameDir ${PROJECT_SOURCE_DIR}/Game)

# GLM
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

# Main Game Files
set(GameHeaders ${GameDir}/Game.hpp)
set(GameLibs ${GameDir}/Game.cpp)

# Includes
list(APPEND GameHeaders ${GameDir}/Includes.hpp)

# GameState
list(APPEND GameHeaders ${GameDir}/GameState/GameState.hpp)
list(APPEND GameHeaders ${GameDir}/GameState/GameStateStart.hpp)
list(APPEND GameHeaders ${GameDir}/GameState/GameStateEditor.hpp)

# General
include_directories(${GameDir})

# Setup
link_directories(${GameDir}/Setup)
include_directories(${GameDir}/Setup)
list(APPEND GameHeaders ${GameDir}/Setup/Setup.hpp)
list(APPEND GameLibs ${GameDir}/Setup/Setup.cpp)

# Setup Parser
link_directories(${GameDir}/Setup/Parser)
include_directories(${GameDir}/Setup/Parser)
list(APPEND GameHeaders ${GameDir}/Setup/Parser/Parser.hpp)
list(APPEND GameLibs ${GameDir}/Setup/Parser/Parser.cpp)

# Names
link_directories(${GameDir}/Names)
include_directories(${GameDir}/Names)
list(APPEND GameHeaders ${GameDir}/Names/Names.hpp)
list(APPEND GameLibs ${GameDir}/Names/Names.cpp)

# Markov
link_directories(${GameDir}/Markov)
include_directories(${GameDir}/Markov)
list(APPEND GameHeaders ${GameDir}/Markov/Markov.hpp)
list(APPEND GameLibs ${GameDir}/Markov/Markov.cpp)

# Settings
link_directories(${GameDir}/Settings)
include_directories(${GameDir}/Settings)
list(APPEND GameHeaders ${GameDir}/Settings/Settings.hpp)
list(APPEND GameLibs ${GameDir}/Settings/Settings.cpp)

# Forest
link_directories(${GameDir}/Forest)
include_directories(${GameDir}/Forest)
list(APPEND GameHeaders ${GameDir}/Forest/Forest.hpp)
list(APPEND GameLibs ${GameDir}/Forest/Forest.cpp)
list(APPEND GameHeaders ${GameDir}/Forest/Tree.hpp)
list(APPEND GameLibs ${GameDir}/Forest/Tree.cpp)
list(APPEND GameHeaders ${GameDir}/Forest/Species.hpp)
list(APPEND GameLibs ${GameDir}/Forest/Species.cpp)

# NordicOS
find_package(NordicOS REQUIRED)
include_directories(${NORDICOS_INCLUDE_DIR})
link_directories(${NORDICOS_LIBRARY_DIR})
add_definitions(${NORDICOS_DEFINITIONS})

# Valkyrie
find_package(Valkyrie REQUIRED)
include_directories(${VALKYRIE_INCLUDE_DIR})
link_directories(${VALKYRIE_LIBRARY_DIR})
add_definitions(${VALKYRIE_DEFINITIONS})

# Build Number
string(TIMESTAMP buildNumber "%j%Y%H%M%S")
file(WRITE ${GameDir}/buildNumber.hpp "#ifndef GAME_BUILDNUMBER\n#define GAME_BUILDNUMBER ${buildNumber}\n#endif")
list(APPEND LibHeaders ${GameDir}/buildNumber.hpp)

# Library
add_library(GameLibrary SHARED ${GameLibs} ${GameHeaders})
set_target_properties(GameLibrary PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(GameLibrary PROPERTIES COMPILE_FLAGS ${EXTRA_FLAGS})

# Linker
if (WIN32)
    target_link_libraries(GameLibrary ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 c++abi)
elseif (APPLE)
    target_link_libraries(GameLibrary "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" c++abi)
elseif (UNIX)
    target_link_libraries(GameLibrary ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB})
endif()

# Link
target_link_libraries(GameLibrary NordicOS)
target_link_libraries(GameLibrary Valkyrie)
