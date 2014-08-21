# CMake Version
cmake_minimum_required(VERSION 2.8)# Project Name

project(Valkyrie)

# C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -m64")
set(EXTRA_FLAGS " -x objective-c++")

# NOS Files
set(BasePath ${PROJECT_SOURCE_DIR}/Valkyrie)
set(LibHeaders ${BasePath}/Valkyrie.hpp)
set(LibSources ${BasePath}/Valkyrie.cpp)

# Build Number
string(TIMESTAMP buildNumber "%j%Y%H%M%S")
file(WRITE ${BasePath}/buildNumber.hpp "#ifndef VALKYRIE_BUILDNUMBER\n#define VALKYRIE_BUILDNUMBER ${buildNumber}\n#endif")
list(APPEND LibHeaders ${BasePath}/buildNumber.hpp)

# NordicOS
find_package(NordicOS REQUIRED)
include_directories(${NORDICOS_INCLIDE_DIR})
link_directories(${NORDICOS_LIBRARY_DIR})
add_definitions(${NORDICOS_DEFINITIONS})

# Generate Library
add_library(Valkyrie STATIC ${LibSources} ${LibHeaders})
set_target_properties(Valkyrie PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Valkyrie PROPERTIES OUTPUT_NAME "NordicOS")

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
