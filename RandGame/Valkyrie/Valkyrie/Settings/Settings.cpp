#include "./Settings.hpp"

namespace NordicArts {
    namespace ValkyrieNS {
        Settings::Settings() {
            std::string cFileName = "./GameFiles/Settings.json";
            
            NordicOS::TextFileReader pFile(cFileName, true);
            std::string cFilePath = pFile.getFilePath();
            
            if (NordicOS::fileExists(cFilePath)) {
                boost::property_tree::ptree pSettings;
                boost::property_tree::read_json(cFilePath, pSettings);
                
                m_sGameSettings.iRefreshRate    = pSettings.get<int>("settings.refreshRate");
                m_sGameSettings.iFOV            = pSettings.get<int>("settings.fov");
                m_sGameSettings.bVSync          = pSettings.get<bool>("settings.vSync");
                m_sGameSettings.bWindowed       = pSettings.get<bool>("settings.windowMode");
                
                BOOST_FOREACH(boost::property_tree::ptree::value_type &resolution, pSettings.get_child("settings.resolution")) {
                    m_sGameSettings.vResolution.x = resolution.second.get<int>("width");
                    m_sGameSettings.vResolution.y = resolution.second.get<int>("height");
                }
            }
        }

        Settings::~Settings() {
        }

        GameSettings Settings::getSettings() const {
            return m_sGameSettings;
        }
    };
};
