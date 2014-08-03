# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(GameLibrary)

# C++11
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -std=c++11 -stdlib=libc++ -m64")
set(EXTRA_FLAGS " -x objective-c++")

# Directories
set(SetupDir ${PROJECT_SOURCE_DIR}/Setup)
set(MainDir ${PROJECT_SOURCE_DIR}/../)

# Main Game Files
set(GameHeaders ${PROJECT_SOURCE_DIR}/Game.h)
set(GameLibs ${PROJECT_SOURCE_DIR}/Game.cpp)

# Includes
list(APPEND GameHeaders ${MainDir}/includes.h)

# OS Specific Includes
include_directories(${MainDir}/Includes)
if (WIN32)
    list(APPEND GameHeaders ${MainDir}/Includes/Windows.h)
elseif(APPLE)
    list(APPEND GameHeaders ${MainDir}/Includes/OSX.h)
elseif(UNIX)
    list(APPEND GameHeaders ${MainDir}/Includes/Linux.h)
endif()

# Setup
link_directories(${SetupDir})
include_directories(${SetupDir})
list(APPEND GameHeaders ${SetupDir}/Setup.h)
list(APPEND GameLibs ${SetupDir}/Setup.cpp)

# Setup Parser
link_directories(${SetupDir}/Parser)
include_directories(${SetupDir}/Parser)
list(APPEND GameHeaders ${SetupDir}/Parser/Parser.h)
list(APPEND GameLibs ${SetupDir}/Parser/Parser.cpp)

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