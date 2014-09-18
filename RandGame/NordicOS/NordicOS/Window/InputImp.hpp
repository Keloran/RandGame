#ifndef NordicArts_NordicOS_Window_InputImp_H
#define NordicArts_NordicOS_Window_InputImp_H

#include "../OS.hpp"

#if defined(NordicOS_Windows)
    #include "../Windows/Input/Input.hpp"
#elif defined(NordicOS_Linux)
    #include "../Linux/Input/Input.hpp"
#elif defined(NordicOS_OSX)
    #include "../OSX/Input/Input.hpp"
#endif

#endif
