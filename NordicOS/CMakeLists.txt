# CMake Version
cmake_minimum_required(VERSION 2.8)# Project Name

project(NordicOS)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -m64")
set(EXTRA_FLAGS " -x objective-c++")

# NOS Files
set(Lib_Headers ${PROJECT_SOURCE_DIR}/OS.hpp)
set(Lib_Source ${PROJECT_SOURCE_DIR}/OS.cpp)

# NOS Loader
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/OSLoad.hpp)

# NOS Folder
set(NOS ${PROJECT_SOURCE_DIR}/NordicOS)

# nonWindows
link_directories(${NOS}/nonWindows)
include_directories(${NOS}/nonWindows)
list(APPEND Lib_Headers ${NOS}/nonWindows/nonWindows.hpp)
list(APPEND Lib_Source ${NOS}/nonWindows/nonWindows.cpp)

# OS Specific Classes
if (WIN32)
    link_directories(${NOS}/Windows)
    include_directories(${NOS}/Windows)
    list(APPEND Lib_Headers ${IR}/Windows/Windows.hpp)
    list(APPEND Lib_Source ${NOS}/Windows/Windows.cpp)
elseif (APPLE)
    link_directories(${NOS}/OSX)
    include_directories(${NOS}/OSX)
    list(APPEND Lib_Headers ${NOS}/OSX/OSX.hpp)
    list(APPEND Lib_Headers ${NOS}/OSX/OSX.mm)
#    list(APPEND Lib_Source ${NOS}/OSX/OSX.cpp)
elseif (UNIX)
    link_directories(${NOS}/Linux)
    include_directories(${NOS}/Linux)
    list(APPEND Lib_Headers ${NOS}/Linux/Linux.hpp)
    list(APPEND Lib_Source ${NOS}/Linux/Linux.cpp)
endif()

# String
link_directories(${NOS}/String)
include_directories(${NOS}/String)
list(APPEND Lib_Headers ${NOS}/String/String.hpp)
list(APPEND Lib_Source ${NOS}/String/String.cpp)

# Time
link_directories(${NOS}/Time)
include_directories(${NOS}/Time)
list(APPEND Lib_Headers ${NOS}/Time/Time.hpp)
list(APPEND Lib_Source ${NOS}/Time/Time.cpp)

# Logger
link_directories(${NOS}/Logger)
include_directories(${NOS}/Logger)
list(APPEND Lib_Headers ${NOS}/Logger/Logger.hpp)
list(APPEND Lib_Source ${NOS}/Logger/Logger.cpp)

# Exception Handler
link_directories(${NOS}/ExceptionHandler)
include_directories(${NOS}/ExceptionHandler)
list(APPEND Lib_Headers ${NOS}/ExceptionHandler/ExceptionHandler.hpp)
list(APPEND Lib_Source ${NOS}/ExceptionHandler/ExceptionHandler.cpp)

# File Handler
link_directories(${NOS}/FileHandler)
include_directories(${NOS}/FileHandler)
list(APPEND Lib_Headers ${NOS}/FileHandler/FileUtils.hpp)
list(APPEND Lib_Headers ${NOS}/FileHandler/FileHandler.hpp)
list(APPEND Lib_Source ${NOS}/FileHandler/FileHandler.cpp)

# TextFile Writer
link_directories(${NOS}/FileHandler/TextFileWriter)
include_directories(${NOS}/FileHandler/TextFileWriter)
list(APPEND Lib_Headers ${NOS}/FileHandler/TextFileWriter/TextFileWriter.hpp)
list(APPEND Lib_Source ${NOS}/FileHandler/TextFileWriter/TextFileWriter.cpp)

# TextFile Reader
link_directorieS(${NOS}/FileHandler/TextFileReader)
include_directories(${NOS}/FileHandler/TextFileReader)
list(APPEND Lib_Headers ${NOS}/FileHandler/TextFileReader/TextFileReader.hpp)
list(APPEND Lib_Source ${NOS}/FileHandler/TextFileReader/TextFileReader.cpp)

# BlockProcess
link_directories(${NOS}/BlockProcess)
include_directories(${NOS}/BlockProcess)
list(APPEND Lib_Headers ${NOS}/BlockProcess/BlockProcess.hpp)
list(APPEND Lib_Source ${NOS}/BlockProcess/BlockProcess.cpp)

# BlockThread
link_directories(${NOS}/BlockThread)
include_directories(${NOS}/BlockThread)
list(APPEND Lib_Headers ${NOS}/BlockThread/BlockThread.hpp)
list(APPEND Lib_Source ${NOS}/BlockThread/BlockThread.cpp)

# Critical Section
link_directories(${NOS}/Critical)
include_directories(${NOS}/Critical)
list(APPEND Lib_Headers ${NOS}/Critical/Critical.hpp)
list(APPEND Lib_Source ${NOS}/Critical/Critical.cpp)

# Mutex
link_directories(${NOS}/Mutex)
include_directories(${NOS}/Mutex)
list(APPEND Lib_Headers ${NOS}/Mutex/Mutex.hpp)
list(APPEND Lib_Source ${NOS}/Mutex/Mutex.cpp)

# Singleton
link_directories(${NOS}/Singleton)
include_directories(${NOS}/Singleton)
list(APPEND Lib_Headers ${NOS}/Singleton/Singleton.hpp)
list(APPEND Lib_Source ${NOS}/Singleton/Singleton.cpp)

# Noise
link_directories(${NOS}/Noise)
include_directories(${NOS}/Noise)
list(APPEND Lib_Headers ${NOS}/Noise/Simplex.hpp)
list(APPEND Lib_Source ${NOS}/Noise/Simplex.cpp)

# Generate Library
add_library(NordicOS STATIC ${Lib_Source} ${Lib_Headers})
set_target_properties(NordicOS PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(NordicOS PROPERTIES OUTPUT_NAME "NordicOS")

# Linker
if (WIN32)
    target_link_libraries(NordicOS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 boost_locale c++abi)
elseif (APPLE)
    target_link_libraries(NordicOS "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" boost_locale c++abi)
elseif (UNIX)
    target_link_libraries(NordicOS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} boost_locale c++abi)
endif()
