# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(NordicOS)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 --stdlib=libc++ -m64")
set(EXTRA_FLAGS " -x objective-c++")

# Output Dir
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../Build/Lib)

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
    list(APPEND LibHeaders ${NOS}/Windows/Windows.hpp)
    list(APPEND LibSources ${NOS}/Windows/Windows.cpp)

    # Window Handle
    link_directories(${NOS}/Windows/Window)
    include_directories(${NOS}/Windows/Window)
    list(APPEND LibHeaders ${NOS}/Windows/Window/WindowHandle.hpp)
elseif (APPLE)
    link_directories(${NOS}/OSX)
    include_directories(${NOS}/OSX)
    list(APPEND LibHeaders ${NOS}/OSX/OSX.hpp)
    list(APPEND LibSources ${NOS}/OSX/OSX.mm)
    list(APPEND LibHeaders ${NOS}/OSX/Wrapper/AutoReleasePool.hpp)
    list(APPEND LibSources ${NOS}/OSX/Wrapper/AutoReleasePool.mm)

    # Application
    link_directories(${NOS}/OSX/Application)
    include_directories(${NOS}/OSX/Application)
    list(APPEND LibHeaders ${NOS}/OSX/Application/Application.hpp)
    list(APPEND LibSources ${NOS}/OSX/Application/Application.mm)
    list(APPEND LibHeaders ${NOS}/OSX/Application/Delegate.hpp)
    list(APPEND LibSources ${NOS}/OSX/Application/Delegate.mm)

    # OpenGL
    link_directories(${NOS}/OSX/OpenGL)
    include_directories(${NOS}/OSX/OpenGL)
    list(APPEND LibHeaders ${NOS}/OSX/OpenGL/View.hpp)
    list(APPEND LibSources ${NOS}/OSX/OpenGL/View.mm)

    # Window Stuff
    link_directories(${NOS}/OSX/Window/Controller)
    include_directorieS(${NOS}/OSX/Window/Controller)
    list(APPEND Libheaders ${NOS}/OSX/Window/Controller/Controller.hpp)
    list(APPEND LibSources ${NOS}/OSX/Window/Controller/Controller.mm)
    
    link_directories(${NOS}/OSX/Window)
    include_directories(${NOS}/OSX/Window)
    list(APPEND LibHeaders ${NOS}/OSX/Window/WindowHandle.hpp)
    list(APPEND LibHeaders ${NOS}/OSX/Window/Window.hpp)
    list(APPEND LibSources ${NOS}/OSX/Window/Window.mm)
    list(APPEND LibHeaders ${NOS}/OSX/Window/DelegateProtocol.hpp)
    list(APPEND LibSources ${NOS}/OSX/Window/VideoModeImp.cpp)

    link_directories(${NOS}/OSX/Window/WindowOS)
    include_directories(${NOS}/OSX/Window/WindowOS)
    list(APPEND LibHeaders ${NOS}/OSX/Window/WindowOS/WindowOS.hpp)
    list(APPEND LibSources ${NOS}/OSX/Window/WindowOS/WindowOS.mm)

    link_directories(${NOS}/OSX/Window/SilentResponder)
    include_directories(${NOS}/OSX/Window/SilentResponder)
    list(APPEND LibHeaders ${NOS}/OSX/Window/SilentResponder/SilentResponder.hpp)
    list(APPEND LibSources ${NOS}/OSX/Window/SilentResponder/SilentResponder.mm)

    # Input
    link_directories(${NOS}/OSX/Input)
    include_directories(${NOS}/OSX/Input)
    list(APPEND LibHeaders ${NOS}/OSX/Input/Input.hpp)
    list(APPEND LibSources ${NOS}/OSX/Input/Input.mm)
    list(APPEND LibHeaders ${NOS}/OSX/Input/HIDInputManager.hpp)
    list(APPEND LibSources ${NOS}/OSX/Input/HIDInputManager.mm)
    list(APPEND LibHeaders ${NOS}/OSX/Input/KeyboardHelper.hpp)
    list(APPEND LibSources ${NOS}/OSX/Input/KeyboardHelper.mm)
    list(APPEND LibHeaders ${NOS}/OSX/Input/KeyboardModifiersHelper.hpp)
    list(APPEND LibSources ${NOS}/OSX/Input/KeyboardModifiersHelper.mm)

    # Application
    link_directories(${NOS}/OSX/Application)
    include_directories(${NOS}/OSX/Application)
    list(APPEND LibHeaders ${NOS}/OSX/Application/Application.hpp)
    list(APPEND LibSources ${NOS}/OSX/Application/Application.mm)
    list(APPEND LibHeaders ${NOS}/OSX/Application/Delegate.hpp)
    list(APPEND LibSources ${NOS}/OSX/Application/Delegate.mm)
    list(APPEND LibHeaders ${NOS}/OSX/Application/Controller.hpp)

    # Conversion
    link_directories(${NOS}/OSX/Conversion)
    include_directories(${NOS}/OSX/Conversion)
    list(APPEND LibHeaders ${NOS}/OSX/Conversion/OBJC.hpp)
    list(APPEND LibSources ${NOS}/OSX/Conversion/OBJC.mm)
    list(APPEND LibHeaders ${NOS}/OSX/Conversion/CG.hpp)
    list(APPEND LibSources ${NOS}/OSX/Conversion/CG.cpp)
elseif (UNIX)
    link_directories(${NOS}/Linux)
    include_directories(${NOS}/Linux)
    list(APPEND LibHeaders ${NOS}/Linux/Linux.hpp)
    list(APPEND LibSources ${NOS}/Linux/Linux.cpp)

    # Window Handle
    link_directories(${NOS}/Linux/Window)
    include_directories(${NOS}/Linux/Window)
    list(APPEND LibHeaders ${NOS}/Linux/Window/WindowHandle.hpp)
endif()

# Window
link_directories(${NOS}/Window)
include_directories(${NOS}/Window)
list(APPEND LibHeaders ${NOS}/Window/Window.hpp)
link_directories(${NOS}/Window/Window)
include_directories(${NOS}/Window/Window)
list(APPEND LibHeaders ${NOS}/Window/Window/Window.hpp)
list(APPEND LibSources ${NOS}/Window/Window/Window.cpp)
list(APPEND LibHeaders ${NOS}/Window/Window/ContextSettings.hpp)
list(APPEND LibHeaders ${NOS}/Window/Window/WindowHandle.hpp)
list(APPEND LibHeaders ${NOS}/Window/Window/WindowStyle.hpp)

# Event
list(APPEND LibHeaders ${NOS}/Window/Event.hpp)

# Maths
link_directories(${NOS}/Maths)
include_directories(${NOS}/Maths)
list(APPEND LibHeaders ${NOS}/Maths/Vector2.hpp)
list(APPEND LibHeaders ${NOS}/Maths/Vector2.inl)
list(APPEND LibHeaders ${NOS}/Maths/Vector3.hpp)
list(APPEND LibHeaders ${NOS}/Maths/Vector3.inl)

# Input
list(APPEND LibHeaders ${NOS}/Window/InputImp.hpp)
link_directories(${NOS}/Window/Mouse)
include_directories(${NOS}/Window/Mouse)
list(APPEND LibHeaders ${NOS}/Window/Mouse/Mouse.hpp)
list(APPEND LibSources ${NOS}/Window/Mouse/Mouse.cpp)
link_directories(${NOS}/Window/Keyboard)
include_directories(${NOS}/Window/Keyboard)
list(APPEND LibHeaders ${NOS}/Window/Keyboard/Keyboard.hpp)
list(APPEND LibSources ${NOS}/Window/Keyboard/Keyboard.cpp)

# Video Mode
link_directories(${NOS}/Window/Window/VideoMode)
include_directories(${NOS}/Window/Window/VideoMode)
list(APPEND LibHeaders ${NOS}/Window/Window/VideoMode/VideoMode.hpp)
list(APPEND LibSources ${NOS}/Window/Window/VideoMode/VideoMode.cpp)
list(APPEND LibHeaders ${NOS}/Window/Window/VideoMode/VideoModeImp.hpp)

# UTF
link_directories(${NOS}/String)
include_directories(${NOS}/String)
list(APPEND LibHeaders ${NOS}/String/UTF.hpp)
list(APPEND LibHeaders ${NOS}/String/UTF.inl)

# String
list(APPEND LibHeaders ${NOS}/String/String.hpp)
list(APPEND LibHeaders ${NOS}/String/String.inl)
list(APPEND LibSources ${NOS}/String/String.cpp)

# Time
link_directories(${NOS}/Time)
include_directories(${NOS}/Time)
list(APPEND LibHeaders ${NOS}/Time/Time.hpp)
list(APPEND LibSources ${NOS}/Time/Time.cpp)
list(APPEND LibHeaders ${NOS}/Time/Sleep.hpp)
list(APPEND LibSources ${NOS}/Time/Sleep.cpp)

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

# Error Handler
list(APPEND LibHeaders ${NOS}/ExceptionHandler/Errors.hpp)
list(APPEND LibSources ${NOS}/ExceptionHandler/Errors.cpp)

# NonCopyable
link_directories(${NOS}/NonCopyable)
include_directories(${NOS}/NonCopyable)
list(APPEND LibHeaders ${NOS}/NonCopyable/NonCopyable.hpp)

# File Handler
link_directories(${NOS}/FileHandler)
include_directories(${NOS}/FileHandler)
list(APPEND LibHeaders ${NOS}/FileHandler/FileUtils.hpp)
list(APPEND LibSources ${NOS}/FileHandler/FileUtils.cpp)
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

# Lock
link_directories(${NOS}/Threading/Lock)
include_directories(${NOS}/Threading/Lock)
list(APPEND LibHeaders ${NOS}/Threading/Lock/Lock.hpp)
list(APPEND LibHeaders ${NOS}/Threading/Lock/Lock.cpp)

# Mutex
link_directories(${NOS}/Threading/Mutex)
include_directories(${NOS}/Threading/Mutex)
list(APPEND LibHeaders ${NOS}/Threading/Mutex/Mutex.hpp)
list(APPEND LibSources ${NOS}/Threading/Mutex/Mutex.cpp)

# Thread
link_directories(${NOS}/Threading/Thread)
include_directories(${NOS}/Threading/Thread)
list(APPEND LibHeaders ${NOS}/Threading/Thread/Thread.hpp)
list(APPEND LibHeaders ${NOS}/Threading/Thread/Thread.inl)
list(APPEND LibSources ${NOS}/Threading/Thread/Thread.cpp)

# ThreadLocal
link_directories(${NOS}/Threading/ThreadLocal)
include_directories(${NOS}/Threading/ThreadLocal)
list(APPEND LibHeaders ${NOS}/Threading/ThreadLocal/ThreadLocal.hpp)
list(APPEND LibSources ${NOS}/Threading/ThreadLocal/ThreadLocal.cpp)
list(APPEND LibHeaders ${NOS}/Threading/ThreadLocal/ThreadLocalPtr.hpp)
list(APPEND LibHeaders ${NOS}/Threading/ThreadLocal/ThreadLocalPtr.inl)

# Threads
link_directories(${NOS}/Threads)
include_directories(${NOS}/Threads)
list(APPEND LibHeaders ${NOS}/Threads/Threads.hpp)
list(APPEND LibSources ${NOS}/Threads/Threads.cpp)

# Sleep
link_directories(${NOS}/Threading/Sleep)
include_directories(${NOS}/Threading/Sleep)
list(APPEND LibHeaders ${NOS}/Threading/Sleep/Sleep.hpp)
list(APPEND LibSources ${NOS}/Threading/Sleep/Sleep.cpp)

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
link_directories(${NOS}/sqlite)
include_directories(${NOS}/sqlite)
add_subdirectory(${NOS}/sqlite)

# Window Stuff
link_directories(${NOS}/Window/Window)
include_directories(${NOS}/Window/Window)
list(APPEND LibHeaders ${NOS}/Window/Window/WindowImp.hpp)
list(APPEND LibSources ${NOS}/Window/Window/WindowImp.hpp)

# GL Stuff
link_directories(${NOS}/Window/Window/GL)
include_directories(${NOS}/Window/Window/GL)
list(APPEND LibSources ${NOS}/Window/Window/GL/Context.cpp)
list(APPEND LibHeaders ${NOS}/Window/Window/GL/Resource.hpp)
list(APPEND LibSources ${NOS}/Window/Window/GL/Resource.cpp)

# Video Mode
link_directories(${NOS}/Window/Window/VideoMode)
include_directories(${NOS}/Window/Window/VideoMode)
list(APPEND LibSources ${NOS}/Window/Window/VideoMode/VideoMode.cpp)
list(APPEND LibHeaders ${NOS}/Window/Window/VideoMode/VideoMode.hpp)
list(APPEND LibHeaders ${NOS}/Window/Window/VideoMode/VideoModeImp.hpp)

# Implementations Stuff
if (WIN32)
    # Mutex    
    link_directories(${NOS}/Windows/Mutex)
    include_directories(${NOS}/Windows/Mutex)
    list(APPEND LibHeaders ${NOS}/Windows/Mutex/Mutex.hpp)
    list(APPEND LibSources ${NOS}/Windows/Mutex/Mutex.cpp)
    
    # Sleep
    link_directories(${NOS}/nonWindows/Sleep)
    include_directories(${NOS}/nonWindows/Sleep)
    list(APPEND LibHeaders ${NOS}/Windows/Sleep/Sleep.hpp)
    list(APPEND LibSources ${NOS}/Windows/Sleep/Sleep.cpp)

    # Thread
    link_directories(${NOS}/Windows/Thread)
    include_directories(${NOS}/Windows/Thread)
    list(APPEND LibHeaders ${NOS}/Windows/Thread/Thread.hpp)    
    list(APPEND LibSources ${NOS}/Windows/Thread/Thread.cpp)

    # ThreadLocal    
    link_directories(${NOS}/Windows/ThreadLocal)
    include_directories(${NOS}/Windows/ThreadLocal)
    list(APPEND LibHeaders ${NOS}/Windows/ThreadLocal/ThreadLocal.hpp)
    list(APPEND LibSources ${NOS}/Windows/ThreadLocal/ThreadLocal.cpp)
else()
    # Mutex
    link_directories(${NOS}/nonWindows/Mutex)
    include_directories(${NOS}/nonWindows/Mutex)
    list(APPEND LibHeaders ${NOS}/nonWindows/Mutex/Mutex.hpp)
    list(APPEND LibSources ${NOS}/nonWindows/Mutex/Mutex.cpp)

    # Sleep
    link_directories(${NOS}/nonWindows/Sleep)
    include_directories(${NOS}/nonWindows/Sleep)
    list(APPEND LibHeaders ${NOS}/nonWindows/Sleep/Sleep.hpp)
    list(APPEND LibSources ${NOS}/nonWindows/Sleep/Sleep.cpp)

    # Thread
    link_directories(${NOS}/nonWindows/Thread)
    include_directories(${NOS}/nonWindows/Thread)
    list(APPEND LibHeaders ${NOS}/nonWindows/Thread/Thread.hpp)
    list(APPEND LibSources ${NOS}/nonWindows/Thread/Thread.cpp)

    # ThreadLocal
    link_directories(${NOS}/nonWindows/ThreadLocal)
    include_directories(${NOS}/nonWindows/ThreadLocal)
    list(APPEND LibHeaders ${NOS}/nonWindows/ThreadLocal/ThreadLocal.hpp)
    list(APPEND LibSources ${NOS}/nonWindows/ThreadLocal/ThreadLocal.cpp)
endif()

# Build Number
string(TIMESTAMP buildNumber "%j%Y%H%M%S")
file(WRITE ${NOS}/buildNumber.hpp "#ifndef NORDICOS_BUILDNUMBER\n#define NORDICOS_BUILDNUMBER ${buildNumber}\n#endif")
list(APPEND LibHeaders ${NOS}/buildNumber.hpp)

# Generate Library
add_library(NordicOS SHARED ${LibSources} ${LibHeaders})
set_target_properties(NordicOS PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(NordicOS PROPERTIES OUTPUT_NAME "NordicOS")

# System Linker
if (WIN32)
    target_link_libraries(NordicOS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 c++abi)
elseif (APPLE)
    target_link_libraries(NordicOS "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" c++abi)
elseif (UNIX)
    target_link_libraries(NordicOS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB})
endif()

# Library Linker
target_link_libraries(NordicOS SQLite)
target_link_libraries(NordicOS boost_locale)
