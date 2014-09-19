//
//  WindowImp.h
//  NordicOS
//
//  Created by Max Hooton on 17/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS__WindowImp_H
#define NordicArts_NordicOS__WindowImp_H

#include "../../OS.hpp"
#include "../../NonCopyable/NonCopyable.hpp"
#include "../../String/String.hpp"
#include "../Event.hpp"
#include "../VideoMode/VideoMode.hpp"
#include "./WindowHandle.hpp"
#include "./ContextSettings.hpp"
#include <queue>
#include <set>

namespace NordicArts {
    namespace NordicOS {
        class WindowImp : NonCopyable {
        // Variables
        public:
        protected:
        private:
            std::queue<Event>           m_qEvents;
            
        // Methods
        public:
            static WindowImp *create(VideoMode mode, const String &cTitle, UINT32 iStyle, const ContextSettings &oSettings);
            static WindowImp *create(WindowHandle hHandle);
            
            virtual ~WindowImp();
            
            bool popEvent(Event &oEvent, bool bBlock);
            
            virtual WindowHandle getSystemHandle() const = 0;
            
            virtual glm::vec2 getPosition() const = 0;
            virtual glm::vec2 getSize() const = 0;
            
            virtual void setPosition(const glm::vec2) = 0;
            virtual void setSize(const glm::vec2 &vSize) = 0;
            virtual void setTitle(const String &cTitle) = 0;
            virtual void setIcon(unsigned int iWidth, unsigned int iHeight, const UINT8 *pPixels) = 0;
            virtual void setVisible(bool bVisible) = 0;
            virtual void setMouseCursorVisible(bool bVisible) = 0;
            virtual void setKeyRepeatEnabled(bool bEnabled) = 0;
            
        protected:
            WindowImp();
            
            void pushEvent(const Event &oEvent);
            
            virtual void processEvents() = 0;
            
        private:
            
        };
    };
};

#endif /* defined(__NordicOS__WindowImp__) */
