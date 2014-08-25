#ifndef NORDICARTS_VALKYRIE_SETTINGS_H
#define NORDICARTS_VALKYRIE_SETTINGS_H

#include "../glm/glm.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

namespace NordicArts {
    namespace ValkyrieNS {
        struct GameSettings {
            int iRefreshRate;
            int iFSAA;
            int iFOV;
            
            bool bWindowed;
            bool bVSync;
            
            glm::uvec2 vResolution;
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
