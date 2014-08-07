# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(GameLibrary)

# Module Finder Path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../CMakeModules/")

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -m64")
set(EXTRA_FLAGS " -x objective-c++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -INordicOS")

# Directories
set(SetupDir ${PROJECT_SOURCE_DIR}/Setup)
set(MainDir ${PROJECT_SOURCE_DIR}/../)

# Main Game Files
set(GameHeaders ${PROJECT_SOURCE_DIR}/Game.hpp)
set(GameLibs ${PROJECT_SOURCE_DIR}/Game.cpp)

# Includes
list(APPEND GameHeaders ${MainDir}/includes.hpp)

# OS Specific Includes
include_directories(${MainDir}/Includes)
if (WIN32)
    list(APPEND GameHeaders ${MainDir}/Includes/Windows.hpp)
elseif(APPLE)
    list(APPEND GameHeaders ${MainDir}/Includes/OSX.hpp)
elseif(UNIX)
    list(APPEND GameHeaders ${MainDir}/Includes/Linux.hpp)
endif()

# General
include_directories(${PROJECT_SOURCE_DIR})

# Setup
link_directories(${SetupDir})
include_directories(${SetupDir})
list(APPEND GameHeaders ${SetupDir}/Setup.hpp)
list(APPEND GameLibs ${SetupDir}/Setup.cpp)

# Setup Parser
link_directories(${SetupDir}/Parser)
include_directories(${SetupDir}/Parser)
list(APPEND GameHeaders ${SetupDir}/Parser/Parser.hpp)
list(APPEND GameLibs ${SetupDir}/Parser/Parser.cpp)

# GLM
include_directories(${PROJECT_SOURCE_DIR}../ThirdParty/General)

find_package(NordicOS REQUIRED)
include_directories(${NORDICOS_INCLIDE_DIR})
link_directories(${NORDICOS_LIBRARY_DIR})
add_definitions(${NORDICOS_DEFINITIONS})

# Library
add_library(GameLibrary STATIC ${GameLibs} ${GameHeaders})
set_target_properties(GameLibrary PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(GameLibrary PROPERTIES COMPILE_FLAGS ${EXTRA_FLAGS})

# Linker
if (WIN32)
    target_link_libraries(GameLibrary ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 boost_locale c++abi)
elseif (APPLE)
    target_link_libraries(GameLibrary "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" boost_locale c++abi)
elseif (UNIX)
    target_link_libraries(GameLibrary ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} boost_locale c++abi)
endif()

# Link
target_link_libraries(GameLibrary NordicOS)
