#include "./GameState.hpp"
#include "./GameStateEditor.hpp"
#include <Valkyrie/Color/Color.hpp>

namespace NordicArts {
    namespace GameNS {
        void GameStateEditor::draw(const int iDT) {
            this->m_pGame->m_pWindow->clear(ValkyrieNS::Color::Black);
            this->m_pGame->m_oWindow->draw(this->m_pGame->background);

            return;
        }

        void GameStateEditor::update(const int iDT) {
            return;
        }

        void GameStateEditor::handleInput() {
            sf::Event oEvent;

            while (this->m_pGame->m_oWindow.pollEvent(oEvent)) {
                switch(oEvent.type) {
                    case sf::Event::Closed: {
                        this->m_pGame->m_oWindow.close();
                        break;
                    }

                    case sf::Event::Resized: {
                        m_oGameView.setSize(oEvent.size.width, oEvent.size.height);
                        m_oGUIView.setSize(oEvent.size.width, oEvent.size.height);

                        this->m_pGame->background.setPosition(this->m_pGame->m_oWindow.mapPixelToCoords(sf::Vector2i(0, 0), this->m_pGUIView));
                        this->m_pGame->background.setScale(
                            (float(oEvent.size.width) / float(this->m_pGame->background.getTexture()->getSize().x)),
                            (float(oEvent.size.height) / float(this->m_pGame->background.getTexture()->getSize().y))
                        );
                        break;
                    }
                
                    default:
                        break;
                }
            }

            return;
        }

        GameStateEditor::GameStateEditor(Game *pGame) {
            this->m_pGame = pGame;

            sf::Vector2f vPos = sf::Vector2f(this->m_pGame->m_oWindow.getSize());
            this->m_oGUIView.setSize(vPos);
            this->m_oGameView.setSize(vPos);

            vPos *= 0.5f;
            this->m_oGUIView.setCenter(vPos);
            this->m_oGameView.setCenter(vPos);
        }
    };
};
