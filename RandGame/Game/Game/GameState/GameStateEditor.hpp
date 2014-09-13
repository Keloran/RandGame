//
//  GameStateEditor.h
//  Game
//
//  Created by Max Hooton on 12/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//


#ifndef NordicArts_Game_GameStateEditor_H
#define NordicArts_Game_GameStateEditor_H

#include "./GameState.hpp"

namespace NordicArts {
    namespace GameNS {
        class GameStateEditor : public GameState {
        // Variables
        public:
        protected:
        private:
            sf::View m_oGameView;
            sf::View m_oGUIView;
            
        // Methods
        public:
            virtual void draw(const int iDT);
            virtual void update(const int iDT);
            virtual void handleInput();
            
            GameStateEditor(Game *pGame);
            
        protected:
        private:
            
        };
    };
};

#endif
