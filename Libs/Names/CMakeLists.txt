# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(Names)

set(Lib_Headers ${PROJECT_SOURCE_DIR}/Names.h)
set(Lib_Source ${PROJECT_SOURCE_DIR}/Names.cpp)

# Generate Library
add_library(Names STATIC ${Lib_Source} ${Lib_Headers})
set_target_properties(Names PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Names PROPERTIES OUTPUT_NAME "Names")

# Linker
if (WIN32)
    target_link_libraries(Names ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 boost_locale c++abi)
elseif (APPLE)
    target_link_libraries(Names "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" boost_locale c++abi)
elseif (UNIX)
    target_link_libraries(Names ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} boost_locale c++abi)
endif()