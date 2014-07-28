#include "./Names.h"

namespace NordicArts {
    Names::Names() {
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
    }

    std::string Names::generateName() {
        std::string returnName;
        
        returnName.append(m_vPrefixes[rand() % 7]);
        returnName.append(m_vStems[rand() % 20]);
        returnName.append(m_vSuffixes[rand() % 16]);

        returnName          = boost::locale::to_title(returnName, m_pLocale);
        
        std::cout << "Name: " << returnName.c_str() << std::endl;

        return returnName;
    }
};
