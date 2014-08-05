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

# nonWindows
link_directories(${PROJECT_SOURCE_DIR}/nonWindows)
include_directories(${PROJECT_SOURCE_DIR}/nonWindows)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/nonWindows/nonWindows.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/nonWindows/nonWindows.cpp)

# OS Specific Classes
if (WIN32)
    link_directories(${PROJECT_SOURCE_DIR}/Windows)
    include_directories(${PROJECT_SOURCE_DIR}/Windows)
    list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/Windows/Windows.hpp)
    list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/Windows/Windows.cpp)
elseif (APPLE)
    link_directories(${PROJECT_SOURCE_DIR}/OSX)
    include_directories(${PROJECT_SOURCE_DIR}/OSX)
    list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/OSX/OSX.hpp)
    list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/OSX/OSX.mm)
#    list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/OSX/OSX.cpp)
elseif (UNIX)
    link_directories(${PROJECT_SOURCE_DIR}/Linux)
    include_directories(${PROJECT_SOURCE_DIR}/Linux)
    list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/Linux/Linux.hpp)
    list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/Linux/Linux.cpp)
endif()

# String
link_directories(${PROJECT_SOURCE_DIR}/String)
include_directories(${PROJECT_SOURCE_DIR}/String)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/String/String.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/String/String.cpp)

# Time
link_directories(${PROJECT_SOURCE_DIR}/Time)
include_directories(${PROJECT_SOURCE_DIR}/Time)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/Time/Time.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/Time/Time.cpp)

# Logger
link_directories(${PROJECT_SOURCE_DIR}/Logger)
include_directories(${PROJECT_SOURCE_DIR}/Logger)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/Logger/Logger.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/Logger/Logger.cpp)

# Exception Handler
link_directories(${PROJECT_SOURCE_DIR}/ExceptionHandler)
include_directories(${PROJECT_SOURCE_DIR}/ExceptionHandler)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/ExceptionHandler/ExceptionHandler.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/ExceptionHandler/ExceptionHandler.cpp)

# File Handler
link_directories(${PROJECT_SOURCE_DIR}/FileHandler)
include_directories(${PROJECT_SOURCE_DIR}/FileHandler)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/FileHandler/FileUtils.hpp)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/FileHandler/FileHandler.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/FileHandler/FileHandler.cpp)

# TextFile Writer
link_directories(${PROJECT_SOURCE_DIR}/FileHandler/TextFileWriter)
include_directories(${PROJECT_SOURCE_DIR}/FileHandler/TextFileWriter)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/FileHandler/TextFileWriter/TextFileWriter.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/FileHandler/TextFileWriter/TextFileWriter.cpp)

# TextFile Reader
link_directorieS(${PROJECT_SOURCE_DIR}/FileHandler/TextFileReader)
include_directories(${PROJECT_SOURCE_DIR}/FileHandler/TextFileReader)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/FileHandler/TextFileReader/TextFileReader.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/FileHandler/TextFileReader/TextFileReader.cpp)

# BlockProcess
link_directories(${PROJECT_SOURCE_DIR}/BlockProcess)
include_directories(${PROJECT_SOURCE_DIR}/BlockProcess)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/BlockProcess/BlockProcess.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/BlockProcess/BlockProcess.cpp)

# BlockThread
link_directories(${PROJECT_SOURCE_DIR}/BlockThread)
include_directories(${PROJECT_SOURCE_DIR}/BlockThread)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/BlockThread/BlockThread.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/BlockThread/BlockThread.cpp)

# Critical Section
link_directories(${PROJECT_SOURCE_DIR}/Critical)
include_directories(${PROJECT_SOURCE_DIR}/Critical)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/Critical/Critical.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/Critical/Critical.cpp)

# Mutex
link_directories(${PROJECT_SOURCE_DIR}/Mutex)
include_directories(${PROJECT_SOURCE_DIR}/Mutex)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/Mutex/Mutex.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/Mutex/Mutex.cpp)

# Singleton
link_directories(${PROJECT_SOURCE_DIR}/Singleton)
include_directories(${PROJECT_SOURCE_DIR}/Singleton)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/Singleton/Singleton.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/Singleton/Singleton.cpp)

# Noise
link_directories(${PROJECT_SOURCE_DIR}/Noise)
include_directories(${PROJECT_SOURCE_DIR}/Noise)
list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/Noise/Simplex.hpp)
list(APPEND Lib_Source ${PROJECT_SOURCE_DIR}/Noise/Simplex.cpp)

# Generate Library
add_library(NordicOS STATIC ${Lib_Source} ${Lib_Headers})
set_target_properties(NordicOS PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(NordicOS PROPERTIES OUTPUT_NAME "NordicOS")
set_target_properties(NordicOS PROPERTIES COMPILE_FLAGS ${EXTRA_FLAGS})

# Linker
if (WIN32)
    target_link_libraries(NordicOS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 boost_locale c++abi)
elseif (APPLE)
    target_link_libraries(NordicOS "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" boost_locale c++abi)
elseif (UNIX)
    target_link_libraries(NordicOS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} boost_locale c++abi)
endif()
