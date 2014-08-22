#include "./Settings.hpp"

namespace NordicArts {
    namespace ValkyrieNS {
        Settings::Settings() {
            boost::property_tree::ptree pSettings;
            boost::property_tree::read_json("./GameFiles/Settings.json", pSettings);
            BOOST_FOREACH(boost::property_tree::ptree::value_type &settings, pSettings.get_child("settings")) {
                m_sGameSettings.iRefreshRate = pSettings.get<int>("refreshRate");
            }
        }

        Settings::~Settings() {
        }

        GameSettings Settings::getSettings() const {
            return m_sGameSettings;
        }
    };
};
