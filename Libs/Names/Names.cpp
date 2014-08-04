#include "./Names.hpp"

namespace NordicArts {
    Names::Names() {
        init();
    }
    Names::Names(Logger *pLogger) : m_pLogger(pLogger) {
        init();
        m_bDebug = true;
    }

    void Names::init() {
        m_pLocale = boost::locale::generator().generate("en_US.UTF-8");

        fillPrefixes();
        fillStems();
        fillSuffixes();
    }

    void Names::fillPrefixes() {
        std::vector<std::string> prefixes;
        
        std::ifstream inFile("./Extras/Names/prefix");
        std::string cLine;
    
        while (std::getline(inFile, cLine)) {
            cLine = boost::locale::to_lower(cLine, m_pLocale);
            prefixes.push_back(cLine);
        }

        m_vPrefixes = prefixes;
    }

    void Names::fillStems() {
        std::vector<std::string> stems;
        
        std::ifstream inFile("./Extras/Names/stems");
        std::string cLine;
    
        while (std::getline(inFile, cLine)) {
            cLine = boost::locale::to_lower(cLine, m_pLocale);
            stems.push_back(cLine);
        }
        
        m_vStems = stems;
    }

    void Names::fillSuffixes() {
        std::vector<std::string> suffixes;
    
        std::ifstream inFile("./Extras/Names/suffix");
        std::string cLine;

        while (std::getline(inFile, cLine)) {
            cLine = boost::locale::to_lower(cLine, m_pLocale);
            suffixes.push_back(cLine);
        }

        m_vSuffixes = suffixes;
    }

    Names::~Names() {
        m_pLogger = nullptr;
    }

    std::string Names::generateName() {
        std::string returnName;

        // Prefix
        std::chrono::high_resolution_clock::time_point timePoint    = std::chrono::high_resolution_clock::now();
        std::chrono::nanoseconds timeDuration                       = std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint.time_since_epoch());
        int timeCount                                               = timeDuration.count();
        srand(timeCount);
        returnName.append(m_vPrefixes[rand() % m_vPrefixes.size()]);

        // Middle
        timePoint       = std::chrono::high_resolution_clock::now();
        timeDuration    = std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint.time_since_epoch());
        timeCount       = timeDuration.count();
        srand(timeCount);
        returnName.append(m_vStems[rand() % m_vStems.size()]);

        // Suffix
        timePoint       = std::chrono::high_resolution_clock::now();
        timeDuration    = std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint.time_since_epoch());
        timeCount       = timeDuration.count();
        srand(timeCount);
        returnName.append(m_vSuffixes[rand() % m_vSuffixes.size()]);

        returnName          = boost::locale::to_title(returnName, m_pLocale);
        
        if (m_bDebug) { 
            std::string cString = "Name: ";
            cString.append(returnName);
            m_pLogger->log(cString);
        }

        return returnName;
    }
};
