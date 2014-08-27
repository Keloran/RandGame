# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(NordicOS)

# C++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 --stdlib=libc++ -m64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
set(EXTRA_FLAGS " -x objective-c++")

# NOS Files
set(NOS ${PROJECT_SOURCE_DIR}/NordicOS)
set(LibHeaders ${NOS}/OS.hpp)
set(LibSources ${NOS}/OS.cpp)

# NOS Loader
list(APPEND LibHeaders ${NOS}/OSLoad.hpp)

# nonWindows
link_directories(${NOS}/nonWindows)
include_directories(${NOS}/nonWindows)
list(APPEND LibHeaders ${NOS}/nonWindows/nonWindows.hpp)

# OS Specific Classes
if (WIN32)
    link_directories(${NOS}/Windows)
    include_directories(${NOS}/Windows)
    list(APPEND LibHeaders ${IR}/Windows/Windows.hpp)
    list(APPEND LibSources ${NOS}/Windows/Windows.cpp)
elseif (APPLE)
    link_directories(${NOS}/OSX)
    include_directories(${NOS}/OSX)
    list(APPEND LibHeaders ${NOS}/OSX/OSX.hpp)
    list(APPEND LibHeaders ${NOS}/OSX/OSX.mm)
elseif (UNIX)
    link_directories(${NOS}/Linux)
    include_directories(${NOS}/Linux)
    list(APPEND LibHeaders ${NOS}/Linux/Linux.hpp)
    list(APPEND LibSources ${NOS}/Linux/Linux.cpp)
endif()

# String
link_directories(${NOS}/String)
include_directories(${NOS}/String)
list(APPEND LibHeaders ${NOS}/String/String.hpp)
list(APPEND LibHeaders ${NOS}/String/String.inl)
list(APPEND LibSources ${NOS}/String/String.cpp)

# Time
link_directories(${NOS}/Time)
include_directories(${NOS}/Time)
list(APPEND LibHeaders ${NOS}/Time/Time.hpp)
list(APPEND LibSources ${NOS}/Time/Time.cpp)

# Logger
link_directories(${NOS}/Logger)
include_directories(${NOS}/Logger)
list(APPEND LibHeaders ${NOS}/Logger/Logger.hpp)
list(APPEND LibSources ${NOS}/Logger/Logger.cpp)

# Exception Handler
link_directories(${NOS}/ExceptionHandler)
include_directories(${NOS}/ExceptionHandler)
list(APPEND LibHeaders ${NOS}/ExceptionHandler/ExceptionHandler.hpp)
list(APPEND LibSources ${NOS}/ExceptionHandler/ExceptionHandler.cpp)

# File Handler
link_directories(${NOS}/FileHandler)
include_directories(${NOS}/FileHandler)
list(APPEND LibHeaders ${NOS}/FileHandler/FileUtils.hpp)
list(APPEND LibHeaders ${NOS}/FileHandler/FileHandler.hpp)
list(APPEND LibSources ${NOS}/FileHandler/FileHandler.cpp)

# TextFile Writer
link_directories(${NOS}/FileHandler/TextFileWriter)
include_directories(${NOS}/FileHandler/TextFileWriter)
list(APPEND LibHeaders ${NOS}/FileHandler/TextFileWriter/TextFileWriter.hpp)
list(APPEND LibSources ${NOS}/FileHandler/TextFileWriter/TextFileWriter.cpp)

# TextFile Reader
link_directorieS(${NOS}/FileHandler/TextFileReader)
include_directories(${NOS}/FileHandler/TextFileReader)
list(APPEND LibHeaders ${NOS}/FileHandler/TextFileReader/TextFileReader.hpp)
list(APPEND LibSources ${NOS}/FileHandler/TextFileReader/TextFileReader.cpp)

# BlockProcess
link_directories(${NOS}/BlockProcess)
include_directories(${NOS}/BlockProcess)
list(APPEND LibHeaders ${NOS}/BlockProcess/BlockProcess.hpp)
list(APPEND LibSources ${NOS}/BlockProcess/BlockProcess.cpp)

# BlockThread
link_directories(${NOS}/BlockThread)
include_directories(${NOS}/BlockThread)
list(APPEND LibHeaders ${NOS}/BlockThread/BlockThread.hpp)
list(APPEND LibSources ${NOS}/BlockThread/BlockThread.cpp)

# Critical Section
link_directories(${NOS}/Critical)
include_directories(${NOS}/Critical)
list(APPEND LibHeaders ${NOS}/Critical/Critical.hpp)
list(APPEND LibSources ${NOS}/Critical/Critical.cpp)

# Mutex
link_directories(${NOS}/Mutex)
include_directories(${NOS}/Mutex)
list(APPEND LibHeaders ${NOS}/Mutex/Mutex.hpp)
list(APPEND LibSources ${NOS}/Mutex/Mutex.cpp)

# Singleton
link_directories(${NOS}/Singleton)
include_directories(${NOS}/Singleton)
list(APPEND LibHeaders ${NOS}/Singleton/Singleton.hpp)
list(APPEND LibSources ${NOS}/Singleton/Singleton.cpp)

# Noise
link_directories(${NOS}/Noise)
include_directories(${NOS}/Noise)
list(APPEND LibHeaders ${NOS}/Noise/Simplex.hpp)
list(APPEND LibSources ${NOS}/Noise/Simplex.cpp)

# SQLite
#link_directories(${NOS}/SQLite)
#include_directories(${NOS}/SQLite)
#add_subdirectory(${NOS}/SQLite)

# Build Number
string(TIMESTAMP buildNumber "%j%Y%H%M%S")
file(WRITE ${NOS}/buildNumber.hpp "#ifndef NORDICOS_BUILDNUMBER\n#define NORDICOS_BUILDNUMBER ${buildNumber}\n#endif")
list(APPEND LibHeaders ${NOS}/buildNumber.hpp)

# Generate Library
add_library(NordicOS STATIC ${LibSources} ${LibHeaders})
set_target_properties(NordicOS PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(NordicOS PROPERTIES OUTPUT_NAME "NordicOS")

# System Linker
if (WIN32)
    target_link_libraries(NordicOS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 c++abi)
elseif (APPLE)
    target_link_libraries(NordicOS "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" c++abi)
elseif (UNIX)
    target_link_libraries(NordicOS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} c++abi)
endif()

# Library Linker
#target_link_libraries(NordicOS SQLite)
target_link_libraries(NordicOS boost_locale)
