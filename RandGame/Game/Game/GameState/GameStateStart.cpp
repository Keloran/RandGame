//
//  GameStateStart.cpp
//  Game
//
//  Created by Max Hooton on 12/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./GameState.hpp"
#include "./GameStateEditor.hpp"
#include "./GameStateStart.hpp"

namespace NordicArts {
    namespace GameNS {
        void GameStateStart::draw(const int iDT) {
            this->m_pGame->m_oWindow.setView(this->m_oView);
            
            this->m_pGame->m_oWindow.clear(ValkyrieNS::Color::Black);
            this->m_pGame->m_oWindow.draw(this->m_pGame->m_oBackground);
            
            return
        }
    };
};
