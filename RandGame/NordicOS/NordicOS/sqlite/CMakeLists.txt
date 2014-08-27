# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(SQLite)

set(Lib_Headers ${PROJECT_SOURCE_DIR}/sqlite3.h)
set(Lib_Source ${PROJECT_SOURCE_DIR}/sqlite3.c)

list(APPEND Lib_Headers ${PROJECT_SOURCE_DIR}/sqlite3ext.h)

add_library(SQLite STATIC ${Lib_Source} ${Lib_Headers})
set_target_properties(SQLite PROPERTIES LINKER_LANGUAGE C)
set_target_properties(SQLite PROPERTIES OUTPUT_NAME "SQLite")

# Linker
if (WIN32)
    target_link_libraries(SQLite ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 boost_locale c++abi)
elseif (APPLE)
    target_link_libraries(SQLite "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" boost_locale c++abi)
elseif (UNIX)
    target_link_libraries(SQLite ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} boost_locale c++abi)
endif()
