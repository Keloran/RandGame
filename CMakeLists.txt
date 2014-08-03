# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(RandGame)

# C++11
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -std=c++11 -stdlib=libc++ -m64")
set(EXTRA_FLAGS " -x objective-c++")

# OpenGL
#find_package(GLUT)
#find_package(OpenGL)
#include_directories(${OPENGL_INCLUDE_DIR})
#include_directories(${GLUT_INCLUDE_DIR})

# XRandR needed
if(LINUX)
    find_package(X11 REQUIRED)
    if(NOT X11_Xrandr_FOUND)
        message(FATAL_ERROR "Xrandr library not found")
    endif()
    include_directories(${X11_INCLUDE_DIR})
endif()

# Directories
set(LIBS_DIR ${PROJECT_SOURCE_DIR}/Libs)
set(GAME_DIR ${PROJECT_SOURCE_DIR}/Game)
set(TOOLS_DIR ${PROJECT_SOURCE_DIR}/Tools)
set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/ThirdParty)

# ThirdParty General
include_directories(${THIRDPARTY_DIR}/General)
link_directories(${THIRDPARTY_DIR}/General)
add_subdirectory(${THIRDPARTY_DIR})

# Main Stuff
set(Main_Headers ${PROJECT_SOURCE_DIR}/Main.h)
set(Main_Libs ${PROJECT_SOURCE_DIR}/Main.cpp)

# Includes
list(APPEND Main_Headers ${PROJECT_SOURCE_DIR}/includes.h)

# OS Specific Includes
include_directories(${PROJECT_SOURCE_DIR}/Includes)
if (WIN32)
    list(APPEND Main_Headers ${PROJECT_SOURCE_DIR}/Includes/Windows.h)
elseif(APPLE)
    list(APPEND Main_Headers ${PROJECT_BINARY_DIR}/Includes/OSX.h)
elseif(UNIX)
    list(APPEND Main_Headers ${PROJECT_SOURCE_DIR}/Includes/Linux.h)
endif()

# Tools
include_directories(${TOOLS_DIR})
link_directories(${TOOLS_DIR})
list(APPEND Main_Headers ${TOOLS_DIR}/Strng/Strng.h)
list(APPEND Main_Libs ${TOOLS_DIR}/Strng/Strng.cpp)

# Libs
include_directories(${LIBS_DIR})
link_directories(${LIBS_DIR})
list(APPEND Main_Headers ${LIBS_DIR}/Markov/Markov.h)
list(APPEND Main_Libs ${LIBS_DIR}/Markov/Markov.cpp) 
list(APPEND Main_Headers ${LIBS_DIR}/Names/Names.h)
list(APPEND Main_Libs ${LIBS_DIR}/Names/Names.cpp)
list(APPEND Main_Headers ${LIBS_DIR}/Simplex/Simplex.h)
list(APPEND Main_Libs ${LIBS_DIR}/Simplex/Simplex.cpp)

# ThirdParty OS Specific
if (WIN32)
    include_directories(${THIRDPARTY_DIR}/Windows)
    link_directories(${THIRDPARTY_DIR}/Windows)
elseif(APPLE)
    include_directories(${THIRDPARTY_DIR}/OSX)
    link_directories(${THIRDPARTY_DIR}/OSX)
elseif(UNIX)
    include_directories(${THIRDPARTY_DIR}/Posix)
    link_directories(${THIRDPARTY_DIR}/Posix)
endif()

# Game
include_directories(${GAME_DIR})
link_directories(${GAME_DIR})
add_subdirectory(${GAME_DIR})

# Executable
add_executable(RandGame ${Main_Libs} ${Main_Headers})
set_target_properties(RandGame PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(RandGame PROPERTIES OUTPUT_NAME "RandGame.app")
set_target_properties(RandGame PROPERTIES COMPILE_FLAGS ${EXTRA_FLAGS})

# Linker
if (WIN32)
    target_link_libraries(RandGame ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 boost_locale c++abi)
elseif (APPLE)
    target_link_libraries(RandGame "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" boost_locale c++abi)
elseif (UNIX)
    target_link_libraries(RandGame ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} boost_locale c++abi)
endif()

target_link_libraries(RandGame ThirdPartyLibs GameLibrary)