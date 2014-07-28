#include "./Names.h"

namespace NordicArts {
    Names::Names() {
        fillPrefixes();
        fillStems();
        fillSuffixes();
    }

    void Names::fillPrefixes() {
        std::vector<std::string> prefixes;
        
        std::ifstream inFile("./Extras/Names/prefix");
        std::string cLine;
    
        std::locale locale = boost::locale::generator().generate("en_US.UTF-8");
        
        while (std::getline(inFile, cLine)) {
            cLine = boost::locale::to_lower(cLine, locale);
            prefixes.push_back(cLine);
        }

        m_vPrefixes = prefixes;
    }

    void Names::fillStems() {
        std::vector<std::string> stems;
        
        std::ifstream inFile("./Extras/Names/stems");
        std::string cLine;
    
        std::locale locale = boost::locale::generator().generate("en_US.UTF-8");
    
        while (std::getline(inFile, cLine)) {
            cLine = boost::locale::to_lower(cLine, locale);
            stems.push_back(cLine);
        }
        
        m_vStems = stems;
    }

    void Names::fillSuffixes() {
        std::vector<std::string> suffixes;
    
        std::ifstream inFile("./Extras/Names/suffix");
        std::string cLine;

        std::locale locale = boost::locale::generator().generate("en_US.UTF-8");

        while (std::getline(inFile, cLine)) {
            cLine = boost::locale::to_lower(cLine, locale);
            suffixes.push_back(cLine);
        }

        m_vSuffixes = suffixes;
    }

    Names::~Names() {
    }

    std::string Names::generateName() {
        std::string returnName = "";
        
        returnName.append(m_vPrefixes[rand() % 7]);
        returnName.append(m_vStems[rand() % 20]);
        returnName.append(m_vSuffixes[rand() % 16]);

        std::locale locale  = boost::locale::generator().generate("en_US.UTF-8");
        returnName          = boost::locale::to_title(returnName, locale);        
        
        std::cout << "Name: " << returnName.c_str() << std::endl;

        return returnName;
    }
};
