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

        glm::vec2 Setup::getResolution() const {
            return glm::vec2(1, 1);
        }
        glm::vec2 Setup::getOpenGL() const {
            return glm::vec2(3, 3);
        }

        bool Setup::isVSync() const {
            return true;
        }

        std::string Setup::getGameName() {
            std::string cName = "Bob";
            return cName;
        }
        
        int Setup::getRefreshRate() const {
            return m_sGameSettings.iRefreshRate;
        }
    };
};
