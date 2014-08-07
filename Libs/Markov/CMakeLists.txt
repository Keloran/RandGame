# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(Markov)

set(Lib_Headers ${PROJECT_SOURCE_DIR}/Markov.hpp)
set(Lib_Source ${PROJECT_SOURCE_DIR}/Markov.cpp)

# Add NordicOS
include_directories(${PROJECT_SOURCE_DIR}/../Tools/OS)
link_directories(${PROJECT_SOURCE_DIR}/../Tools/OS)

# Generate Library
add_library(Markov STATIC ${Lib_Source} ${Lib_Headers})
set_target_properties(Markov PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Markov PROPERTIES OUTPUT_NAME "Markov")

# Linker
if (WIN32)
    target_link_libraries(Markov ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 boost_locale c++abi)
elseif (APPLE)
    target_link_libraries(Markov "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" boost_locale c++abi)
elseif (UNIX)
    target_link_libraries(Markov ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} boost_locale c++abi)
endif()

# Link libraries
target_link_libraries(Markov NordicOS)
