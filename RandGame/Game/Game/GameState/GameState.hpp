//
//  GameState.h
//  Game
//
//  Created by Max Hooton on 10/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_Game_GameState_H
#define NordicArts_Game_GameState_H

#include "../Game.hpp"

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
            virtual void draw(const int iDT) = 0;
            virtual void update(const int iDT) = 0;
            virtual void handleInput() = 0;

            virtual ~GameState() { m_pGame = nullptr; };
            
        protected:
        private:
            
        };
    };
};

#endif
