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

        void GameStateStart::update(const int iDT) {
        }

        void GameStateStart::handleInput() {
            sf::Event oEvent;

            while(this->m_pGame->m_oWindow.pollEvent(oEvent)) {
                switch(oEvent.type) {
                    case sf::Event::Closed: {
                        m_pGame->m_oWindow.close();
                        break;
                    }

                    case sf::Event::Resized: {
                        this->m_oView.setSize(oEvent.size.width, oEvent.size.height);
                        this->m_pGame->m_oBackground.setPosition(this->m_pGame->m_oWindow.mapPixelToCoords(sf::Vector2i(0, 0)));
                        this->m_pGame->m_oBackground.setScale(
                            (float(oEvent.size.width) / float(this->m_pGame->m_oBackground.getTexture()->getSize().x)),
                            (float(oEvent.size.height) / float(this->m_pGame->m_oBackground.getTexture()->getSize().y))
                        );
                        break;
                    }

                    case sf::Event::KeyPressed: {
                        if (oEvent.key.pressed == sf::Keyboard::Escape) {
                            this->m_pGame->m_oWindow.close();
                        }
                        break;
                    }

                    default:
                        break;
                }
            }

            return;
        }

        void GameStateStart::loadGame() {
            this->m_pGame->pushState(new GameStateEditor(this->m_pGame));
        
            return;
        }
    };
};
