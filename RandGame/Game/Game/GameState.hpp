//
//  GameState.h
//  Game
//
//  Created by Max Hooton on 10/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef Game_GameState_H
#define Game_GameState_H

#include "./Game.hpp"

namespace NordicArts {
    namespace GameNS {
        class GameState {
        // Variables
        public:
            Game *m_pGame;
            
        protected:
        private:
            
        // Methods
        public:
            virtual void draw(const float fDT) = 0;
            
        protected:
        private:
            
        };
    };
};

#endif
