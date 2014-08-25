#ifndef NORDICARTS_VALKYRIE_SETTINGS_H
#define NORDICARTS_VALKYRIE_SETTINGS_H

#include "../glm/glm.hpp"

#include <NordicOS/FileHandler/TextFileReader/TextFileReader.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

namespace NordicArts {
    namespace ValkyrieNS {
        struct GameSettings {
            int iRefreshRate    = 60;
            int iFSAA           = 0;
            int iFOV            = 75;
            
            bool bWindowed      = false;
            bool bVSync         = false;
            
            glm::uvec2 vResolution  = glm::uvec2(800, 600);
            glm::uvec2 vOpenGL      = glm::uvec2(3, 3);
            
            std::string cGameName   = "Bob";
        };

        class Settings {
            // Variables
            public:
            protected:
            private:
                GameSettings m_sGameSettings;

            // Methods
            public:
                Settings();
                virtual ~Settings();

                GameSettings getSettings() const;

            protected:
            private:

        };
    };
};

#endif
