#include "./Setup.hpp"

namespace NordicArts {
	Setup::Setup() {
	}

	Setup::~Setup() {
	}

	bool Setup::doSetup() {

		return false;
	}

	bool Setup::checkForDatabase() {
		return false;
	}

	void Setup::createDatabase() {
		
	}

    glm::vec2 Setup::getResolution() {
        return glm::vec2(1, 1);    
    }
    glm::vec2 Setup::getOpenGL() {
        return glm::vec2(3, 3);
    }

    bool Setup::isVSync() {
        return true;
    }

    std::string Setup::getGameName() {
        std::string cName = "Bob";
        return cName;
    }
};
