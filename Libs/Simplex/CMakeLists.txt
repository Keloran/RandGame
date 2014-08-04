# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(Simplex)

set(Lib_Headers ${PROJECT_SOURCE_DIR}/Simplex.h)
set(Lib_Source ${PROJECT_SOURCE_DIR}/Simplex.cpp)

# Generate Library
add_library(Simplex STATIC ${Lib_Source} ${Lib_Headers})
set_target_properties(Simplex PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Simplex PROPERTIES OUTPUT_NAME "Simplex")

# Linker
if (WIN32)
    target_link_libraries(Simplex ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 boost_locale c++abi)
elseif (APPLE)
    target_link_libraries(Simplex "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" boost_locale c++abi)
elseif (UNIX)
    target_link_libraries(Simplex ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} boost_locale c++abi)
endif()