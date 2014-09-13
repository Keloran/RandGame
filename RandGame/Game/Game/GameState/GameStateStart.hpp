//
//  GameStateStart.h
//  Game
//
//  Created by Max Hooton on 12/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_Game_GameStateStart_H
#define NordicArts_Game_GameStateStart_H

#include "../Includes.hpp"
#include "./GameState.hpp"

namespace NordicArts {
    namespace GameNS {
        class GameStateStart : public GameState {
        // Variables
        public:
        protected:
        private:
            sf::View m_oView;
            
        // Methods
        public:
            virtual void draw(const int iDT);
            virtual void update(const int iDT);
            virtual void handleInput();
            
            GameStateStart(Game *pGame);
            
        protected:
        private:
            
        };
    };
};

#endif
