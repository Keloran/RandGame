# CMake Version
cmake_minimum_required(VERSION 2.8)

# Project Name
project(ThirdPartyLibs)

set(GeneralDir ${PROJECT_SOURCE_DIR}/General)

# Defines
set(Lib_Headers ${GeneralDir}/sqlite/sqlite3.h)
set(Lib_Libs ${GeneralDir}/sqlite/sqlite3.c)

# SQLite3 Extension
list(APPEND ${Lib_Headers} ${GeneralDir}/sqlite/sqlite3ext.h)

# Create Library
add_library(ThirdPartyLibs STATIC ${Lib_Libs} ${Lib_Headers})
set_target_properties(ThirdPartyLibs PROPERTIES LINKER_LANGUAGE C)
set_target_properties(ThirdPartyLibs PROPERTIES OUTPUT_NAME "ThirdPartyLibs")

# Linker
if (WIN32)
    target_link_libraries(ThirdPartyLibs ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} winmm gdi32 boost_locale c++abi)
elseif (APPLE)
    target_link_libraries(ThirdPartyLibs "-framework Foundation -framework AppKit -framework IOKit -framework Carbon -framework OpenGL -framework CoreFoundation -framework OpenAL -framework GameKit -framework GLKit" boost_locale c++abi)
elseif (UNIX)
    target_link_libraries(ThirdPartyLibs ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${X11_X11_LIB} ${X11_Xrandr_LIB} boost_locale c++abi)
endif()