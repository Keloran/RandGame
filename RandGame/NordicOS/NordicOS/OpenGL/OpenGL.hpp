#ifndef NordicArts_NordicOS_OpenGL_H
#define NordicArts_NordicOS_OpenGL_H

#include "../OS.hpp"

#if defined(NordicOS_Windows)
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#elif defined(NordicOS_Linux)
    #include <GL/gl.h>
    #include <GL/glu.h>
#elif defined(NordicOS_OSX)
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#endif

#endif
