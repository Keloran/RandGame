#ifndef NordicArts_NordicOS_Window_WindowHandle_H
#define NordicArts_NordicOS_Window_WindowHandle_H

#include "../../OS.hpp"
#if defined(NordicOS_Windows)
    #include "../../Widows/Window/WindowHandle.hpp"
#elif defined(NordicOS_OSX)
    #include "../../OSX/Window/WindowHandle.hpp"
#else
    #include "../../Linux/Window/WindowHandle.hpp"
#endif
#endif
