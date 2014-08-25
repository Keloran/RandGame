#include "./Setup.hpp"

namespace NordicArts {
    namespace GameNS {
    	Setup::Setup() {
    	}

    	Setup::~Setup() {
    	}

    	bool Setup::doSetup() {
            ValkyrieNS::Settings::Settings pSettings;
            m_sGameSettings = pSettings.getSettings();

    		return false;
    	}

    	bool Setup::checkForDatabase() {
    		return false;
    	}

    	void Setup::createDatabase() {

    	}
        
        void Setup::setOpenGL(glm::uvec2 vOpenGL) {
            m_sGameSettings.vOpenGL = vOpenGL;
        }
        void Setup::setGameName(std::string cGameName) {
            m_sGameSettings.cGameName = cGameName;
        }

        glm::vec2 Setup::getResolution() const {
            return m_sGameSettings.vResolution;
        }
        glm::vec2 Setup::getOpenGL() const {
            return m_sGameSettings.vOpenGL;
        }

        bool Setup::isVSync() const {
            return m_sGameSettings.bVSync;
        }

        std::string Setup::getGameName() {
            return m_sGameSettings.cGameName;
        }
        
        int Setup::getRefreshRate() const {
            return m_sGameSettings.iRefreshRate;
        }
    };
};
