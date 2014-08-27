# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(RandGame)

# Module Finder Path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules/")

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 --stdlib=libc++ -m64")
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
set(GAME_DIR ${PROJECT_SOURCE_DIR}/Game)
set(THIRDPARTY_DIR ${PROJECT_SOURCE_DIR}/ThirdParty)

# Main Stuff
set(Main_Headers ${PROJECT_SOURCE_DIR}/Main/Main.hpp)
set(Main_Libs ${PROJECT_SOURCE_DIR}/Main/Main.cpp)

# Includes
list(APPEND Main_Headers ${PROJECT_SOURCE_DIR}/Main/includes.hpp)

# NordicOS
find_package(NordicOS)
include_directories(${NORDICOS_INCLUDE_DIR})
link_directories(${NORDICOS_LIBRARY_DIR})
add_definitions(${NORDICOS_DEFINITIONS})
add_subdirectory(${PROJECT_SOURCE_DIR}/NordicOS)

# Valkyrie
find_package(Valkyrie)
include_directories(${VALKYRIE_INCLUDE_DIR})
link_directories(${VALKYRIE_INCLUDE_DIR})
add_subdirectory(${PROJECT_SOURCE_DIR}/Valkyrie)

# Game
include_directories(${GAME_DIR})
link_directories(${GAME_DIR})
add_subdirectory(${GAME_DIR})

# Build Number
string(TIMESTAMP buildNumber "%j%Y%H%M%S")
file(WRITE ${PROJECT_SOURCE_DIR}/Main/buildNumber.hpp "#ifndef RANDGAME_BUILDNUMBER\n#define RANDGAME_BUILDNUMBER ${buildNumber}\n#endif")
list(APPEND LibHeaders ${PROJECT_SOURCE_DIR}/Main/buildNumber.hpp)

# Executable
add_executable(RandGame ${Main_Libs} ${Main_Headers})
set_target_properties(RandGame PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(RandGame PROPERTIES OUTPUT_NAME "RandGame.app")
set_target_properties(RandGame PROPERTIES COMPILE_FLAGS ${EXTRA_FLAGS})

# Linker
if (WIN32)
    target_link_libraries(RandGame ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 c++abi)
elseif (APPLE)
    target_link_libraries(RandGame "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" c++abi)
elseif (UNIX)
    target_link_libraries(RandGame ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} c++abi)
endif()

target_link_libraries(RandGame SQLite)
target_link_libraries(RandGame GameLibrary)
target_link_libraries(RandGame NordicOS)
target_link_libraries(RandGame Valkyrie)
