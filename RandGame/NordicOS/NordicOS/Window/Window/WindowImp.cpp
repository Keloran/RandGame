//
//  WindowImp.cpp
//  NordicOS
//
//  Created by Max Hooton on 17/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./WindowImp.hpp"
#include "../Event/Event.hpp"
#include "../../Threading/Sleep/Sleep.hpp"
#include <algorithm>
#include <cmath>

#if defined(NordicOS_Windows)
    #include "../../Windows/Window/Window.hpp"
#elif defined(NordicOS_Linux)
    #include "../../Linux/Window/Window.hpp"
#elif defined(NordicOS_OSX)
    #include "../../OSX/Window/WindowOS.hpp"
#endif

namespace NordicArts {
    namespace NordicOS {
        WindowImp *WindowImp::create(VideoMode mode, const String &cTitle, UINT32 iStyle, const ContextSettings &oSettings) {
            return new WindowOS(mode, cTitle, iStyle, oSettings);
        }
        
        WindowImp *WindowImp::create(WindowHandle hHandle) {
            return new WindowOS(hHandle);
        }
        
        WindowImp::WindowImp() {
        }
        
        WindowImp::~WindowImp() {
        }
        
        bool WindowImp::popEvent(Event &oEvent, bool bBlock) {
            if (m_qEvents.empty()) {
                processEvents();
            
                if (bBlock) {
                    while (m_qEvents.empty()) {
                        sleep(milliseconds(10));
                        processEvents();
                    }
                }
            }
            
            if(!m_qEvents.empty()) {
                oEvent = m_qEvents.front();
                
                m_qEvents.pop();
                
                return true;
            }
            
            return false;
        }
        
        void WindowImp::pushEvent(const Event &oEvent) {
            m_qEvents.push(oEvent);
        }
    };
};
