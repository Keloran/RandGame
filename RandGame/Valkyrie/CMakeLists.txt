# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(Valkyrie)

# Output Dir
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../Build/Lib)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 --stdlib=libc++ -m64")
set(EXTRA_FLAGS " -x objective-c++")

# Module Finder Path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../CMakeModules/")

# GLM
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

# SFML
find_package(SFML REQUIRED system window graphics audio network)
include_directories(${SFML_INCLUDE_DIR})

# NordicOS
find_package(NordicOS REQUIRED)
include_directories(${NORDICOS_INCLUDE_DIR})
link_directories(${NORDICOS_LIBRARY_DIR})
add_definitions(${NORDICOS_DEFINITIONS})

# Valkyrie Files
set(BasePath ${PROJECT_SOURCE_DIR}/Valkyrie)
set(LibHeaders ${BasePath}/Valkyrie.hpp)
set(LibSources ${BasePath}/Valkyrie.cpp)

# Includes
list(APPEND LibHeaders ${BasePath}/Includes.hpp)

# Color
list(APPEND LibHeaders ${BasePath}/Color/Color.hpp)
list(APPEND LibSources ${BasePath}/Color/Color.cpp)

# Window
list(APPEND LibHeaders ${BasePath}/Window/Window.hpp)
list(APPEND LibSources ${BasePath}/Window/Window.cpp)

# Settings
list(APPEND LibHeaders ${BasePath}/Settings/Settings.hpp)
list(APPEND LibSources ${BasePath}/Settings/Settings.cpp)

# Build Number
string(TIMESTAMP buildNumber "%j%Y%H%M%S")
file(WRITE ${BasePath}/buildNumber.hpp "#ifndef VALKYRIE_BUILDNUMBER\n#define VALKYRIE_BUILDNUMBER ${buildNumber}\n#endif")
list(APPEND LibHeaders ${BasePath}/buildNumber.hpp)

# Generate Library
add_library(Valkyrie SHARED ${LibSources} ${LibHeaders})
set_target_properties(Valkyrie PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Valkyrie PROPERTIES OUTPUT_NAME "Valkyrie")

# System Linker
if (WIN32)
    target_link_libraries(Valkyrie ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 c++abi)
elseif (APPLE)
    target_link_libraries(Valkyrie "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" c++abi)
elseif (UNIX)
    target_link_libraries(Valkyrie ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} c++abi)
endif()

# Library Linker
target_link_libraries(Valkyrie NordicOS)
target_link_libraries(Valkyrie ${SFML_LIBRARIES})
