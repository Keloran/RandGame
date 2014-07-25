#include "./Markov.h"

namespace NordicArts {
    Markov::Markov() {
        fillNameList();

        std::map<std::string, double> firstLetterMap = generateFirstLetterMap();
        m_firstLetterChance = firstLetterMap;
        
        std::map<std::string, double> lastLetterMap = generateLastLetterMap();
        m_lastLetterChance = lastLetterMap;    

        std::map<std::string, std::map<std::string, double> > letterToLetterMap = generateLetterToLetterMap();
        m_letterToLetterChance = letterToLetterMap;
    }

    std::string Markov::generateWord() {
        std::string word = "";
        int i = 0;

        while (true) {
            int randLetter              = (rand() % 27);
            char cLetter                = m_aAlphabet[randLetter];
            std::string firstLetter     = getString(cLetter);

            double randChance           = ((double)rand() / RAND_MAX);
            double randLetterValue      = m_firstLetterChance[firstLetter];
            double randMath             = ((m_firstLetterChance[firstLetter] * 2) + 0.05);

            if (randChance < randMath) {
                word += word.append(firstLetter);
                break;
            }
        }

        std::cout << "Word: " << word.c_str() << std::endl;

        return word;
    }

    void Markov::fillNameList() {
        std::vector<std::string> names;

        std::ifstream inFile("./Extras/names");
        std::string cLine;

        std::locale locale = boost::locale::generator().generate("en_US.UTF-8");

        while (std::getline(inFile, cLine)) {
            cLine = boost::locale::to_lower(cLine, locale);
            names.push_back(cLine);
        }

        // Set the names
        m_vNames = names;
    }

    std::map<std::string, double> Markov::generateFirstLetterMap() {
        std::map<std::string, double> map = getAlphabetMap();

        double total = 0;
        for (std::string c : m_vNames) {
            // create the char
            char *name = new char[(c.size() + 1)];
            name[c.size()] = 0;
            memcpy(name, c.c_str(), c.size());
            
            std::string s = getString(name[0]);

            if (map.find(s) != map.end()) {
                double mapValue = map[s];
                mapValue += 1;
                map[s] = mapValue;

                total++;
            }
        }

        // find the percentage
        for (int i = 0; i < m_aAlphabet[i] != '\0'; i++) {
            // turn the character into a string
            std::string s = getString(m_aAlphabet[i]);
        
            // set value
            map[s] = (map[s] / total);
            std::cout << "Map -- Letter:" << s.c_str() << ", Percent: " << map[s] << std::endl;
        }

        return map;
    }

    std::map<std::string, double> Markov::generateLastLetterMap() {
        std::map<std::string, double> map = getAlphabetMap();
        
        double total = 0;
        for (std::string c : m_vNames) {
            // create the char
            char *name = new char[(c.size() + 1)];
            name[c.size()] = 0;
            memcpy(name, c.c_str(), c.size());

            // turn the last letter into a string
            std::string s = getString(name[(c.size() - 1)]);

            if (map.find(s) != map.end()) {
                double mapValue = map[s];
                mapValue += 1;
                map[s] = mapValue;
                
                total++;
            }
        }

        for (int i = 0; i < m_aAlphabet[i] != '\0'; i++) {
            // turn the character into a string
            std::string s = getString(m_aAlphabet[i]);

            // set value
            map[s] = (map[s] / total);
        }

        return map;
    }

    std::map<std::string, std::map<std::string, double> > Markov::generateLetterToLetterMap() {
        std::map<std::string, std::map<std::string, double> > map;

        // create the map    
        for (int i = 0; i < m_aAlphabet[i] != '\0'; i++) {
            std::string s = getString(m_aAlphabet[i]);
            map[s] = getAlphabetMap();
        }

        // count the amount of times 2 letter appear next to each other
        for (std::string c : m_vNames) {
            char *name = new char[(c.size() + 1)];
            name[c.size()] = 0;
            memcpy(name, c.c_str(), c.size());
    
            for (int i = 0; i < name[i] != '\0'; i++) {
                std::string firstChar   = getString(name[i]);
                std::string secondChar  = getString(name[(i + 1)]);

                if (map.find(firstChar) != map.end()) {
                    if (map[firstChar].find(secondChar) != map[firstChar].end()) {
                        double mapValue = map[firstChar][secondChar];
                        mapValue += 1;

                        map[firstChar][secondChar] = mapValue;
                    }
                }
            }
        }

        for (int i = 0; i < m_aAlphabet[i] != '\0'; i++) {
            std::string firstChar = getString(m_aAlphabet[i]);

            double total = 0;
            if (map.find(firstChar) != map.end()) {
                for (std::map<std::string, double>::iterator i = map[firstChar].begin(); i != map[firstChar].end(); ++i) {
                    std::string secondChar = i->first;
                    
                    if (map[firstChar].find(secondChar) != map[firstChar].end()) {
                        total += map[firstChar][secondChar];
                    }
                }
            }

            for (int j = 0; j < m_aAlphabet[j] != '\0'; j++) {
                std::string secondChar = getString(m_aAlphabet[j]);
                double mapValue = (map[firstChar][secondChar] / total);
                map[firstChar][secondChar] = mapValue;
            }
        }

        return map;
    }

    std::string Markov::getString(char c) {
        std::stringstream ss;
        std::string s;
        
        ss << c;
        ss >> s;

        return s;
    }

    std::map<std::string, double> Markov::getAlphabetMap() {
        std::map<std::string, double> map;
        
        double d = 0;
        for (int i = 0; i < m_aAlphabet[i] != '\0'; i++) {
            std::string s = getString(m_aAlphabet[i]);
            map[s] = d;
        }

        return map;
    }

    Markov::~Markov() {
    }
};
