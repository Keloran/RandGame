//
//  Header.h
//  NordicOS
//
//  Created by Max Hooton on 20/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_Window_VideoModeImp_H
#define NordicArts_NordicOS_Window_VideoModeImp_H

#include "./VideoMode.hpp"

namespace NordicArts {
    namespace NordicOS {
        class VideoModeImp {
        // Variables
        public:
        protected:
        private:
            
        // Methods
        public:
            static std::vector<VideoMode> getFullScreenModes();
            
            static VideoMode getDesktopMode();
            
        protected:
        private:
            
        };
    };
};

#endif
