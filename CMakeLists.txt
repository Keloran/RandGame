# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(RandGame)

# Module Finder Path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -m64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${PROJECT_SOURCE_DIR}/ThirdParty/General/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${PROJECT_SOURCE_DIR}/Tools")
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
include_directories(${THIRDPARTY_DIR}/General/sqlite)
link_directories(${THIRDPARTY_DIR}/General/sqlite)
add_subdirectory(${THIRDPARTY_DIR}/General/sqlite)

# Main Stuff
set(Main_Headers ${PROJECT_SOURCE_DIR}/Main.hpp)
set(Main_Libs ${PROJECT_SOURCE_DIR}/Main.cpp)

# Includes
list(APPEND Main_Headers ${PROJECT_SOURCE_DIR}/includes.hpp)

# OS Specific Includes
include_directories(${PROJECT_SOURCE_DIR}/Includes)
if (WIN32)
    list(APPEND Main_Headers ${PROJECT_SOURCE_DIR}/Includes/Windows.hpp)
elseif(APPLE)
    list(APPEND Main_Headers ${PROJECT_BINARY_DIR}/Includes/OSX.hpp)
elseif(UNIX)
    list(APPEND Main_Headers ${PROJECT_SOURCE_DIR}/Includes/Linux.hpp)
endif()

# Libs
include_directories(${LIBS_DIR})
link_directories(${LIBS_DIR})

include_directories(${LIBS_DIR}/Markov)
link_directories(${LIBS_DIR}/Markov)
add_subdirectory(${LIBS_DIR}/Markov)

include_directories(${LIBS_DIR}/Names)
link_directories(${LIBS_DIR}/Names)
add_subdirectory(${LIBS_DIR}/Names)

# NordicOS
include_directories(${TOOLS_DIR})
link_directories(${TOOLS_DIR}/OS)
add_subdirectory(${TOOLS_DIR}/OS)

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

target_link_libraries(RandGame SQLite GameLibrary)
target_link_libraries(RandGame Markov Names)
target_link_libraries(RandGame NordicOS)
