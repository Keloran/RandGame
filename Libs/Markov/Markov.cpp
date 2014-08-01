#include "./Markov.h"

namespace NordicArts {
    Markov::Markov() {
        // Set the locale
        m_pLocale = boost::locale::generator().generate("en_US.UTF-8");
        
        // read the file
        fillNameList();

        // generate the chance maps
        generateFirstLetterMap();
        generateLastLetterMap();
        generateLetterToLetterMap();
    }

    void Markov::setVariance(float fVariance) {
        m_fVariance = fVariance;
    }

    std::string Markov::generateWord() {
        std::string word = "";
        int i = 0;

        // Seed
        std::chrono::high_resolution_clock::time_point timePoint    = std::chrono::high_resolution_clock::now();
        std::chrono::nanoseconds timeDuration                       = std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint.time_since_epoch());
        int timeCount                                               = timeDuration.count();
        srand(timeCount);

        // generate first letter
        while (true) {
            int randLetter              = (rand() % 27);
            char cLetter                = m_cAlphabet[randLetter];
            std::string firstLetter     = getString(cLetter);

            double randChance           = ((double)rand() / RAND_MAX);
            double randLetterValue      = m_mFirstLetterChance[firstLetter];
            double randMath             = ((m_mFirstLetterChance[firstLetter] * 2) + .05);

            if (randChance < randMath) {
                word.append(firstLetter);
                break;
            }
        }

        // Seed
        timePoint       = std::chrono::high_resolution_clock::now();
        timeDuration    = std::chrono::duration_cast<std::chrono::nanoseconds>(timePoint.time_since_epoch());
        timeCount       = timeDuration.count();
        srand(timeCount);

        // generate word
        while (true) {
            int randLetter              = (rand() % 27);
            char cLetter                = m_cAlphabet[randLetter];
            std::string nextLetter      = getString(cLetter);

            std::string lastLetter      = getString(word.back());
            double nextLetterChance     = ((m_mLetterToLetterChance[lastLetter][nextLetter] * 2) - m_fVariance);
            double randChance           = ((double)rand() / RAND_MAX);

            if (randChance < nextLetterChance) {
                word.append(nextLetter);

                // check if word should end
                lastLetter          = getString(word.back());
                double extraChance  = m_mLastLetterChance[lastLetter];
                double moreRand     = ((double)rand() / RAND_MAX);
                if ((word.size() >= 4) && (moreRand < ((extraChance * 1.5) + .05))) {
                    break;
                } else if ((word.size() > 8) && (moreRand < .3)) {
                    break;
                }
            }
        }

        word = boost::locale::to_title(word, m_pLocale);

        std::cout << "Word: " << word.c_str() << std::endl;

        return word;
    }

    void Markov::fillNameList() {
        std::vector<std::string> names;

        std::ifstream inFile("./Extras/Names/names-list");
        std::string cLine;

        while (std::getline(inFile, cLine)) {
            cLine = boost::locale::to_lower(cLine, m_pLocale);
            names.push_back(cLine);
        }

        // Set the names
        m_vNames = names;
    }

    void Markov::generateFirstLetterMap() {
        std::map<std::string, double> map = getAlphabetMap();

        double total = 0;
        for (std::string c : m_vNames) {
            // create the char
            char *name      = new char[(c.size() + 1)];
            name[c.size()]  = 0;
            memcpy(name, c.c_str(), c.size());
            
            std::string s = getString(name[0]);

            if (map.find(s) != map.end()) {
                double mapValue = map[s];
                mapValue       += 1;
                map[s]          = mapValue;

                total++;
            }
        }

        // find the percentage
        for (int i = 0; i < m_cAlphabet[i] != '\0'; i++) {
            // turn the character into a string
            std::string s = getString(m_cAlphabet[i]);
        
            // set value
            map[s] = (map[s] / total);
        }

        m_mFirstLetterChance = map;
    }

    void Markov::generateLastLetterMap() {
        std::map<std::string, double> map = getAlphabetMap();
        
        double total = 0;
        for (std::string c : m_vNames) {
            // create the char
            char *name      = new char[(c.size() + 1)];
            name[c.size()]  = 0;
            memcpy(name, c.c_str(), c.size());

            // turn the last letter into a string
            std::string s = getString(name[(c.size() - 1)]);

            if (map.find(s) != map.end()) {
                double mapValue = map[s];
                mapValue       += 1;
                map[s]          = mapValue;
                
                total++;
            }
        }

        for (int i = 0; i < m_cAlphabet[i] != '\0'; i++) {
            // turn the character into a string
            std::string s = getString(m_cAlphabet[i]);

            // set value
            map[s] = (map[s] / total);
        }

        m_mLastLetterChance = map;
    }

    void Markov::generateLetterToLetterMap() {
        std::map<std::string, std::map<std::string, double> > map;

        // create the map    
        for (int i = 0; i < m_cAlphabet[i] != '\0'; i++) {
            std::string s   = getString(m_cAlphabet[i]);
            map[s]          = getAlphabetMap();
        }

        // count the amount of times 2 letter appear next to each other
        for (std::string c : m_vNames) {
            char *name      = new char[(c.size() + 1)];
            name[c.size()]  = 0;
            memcpy(name, c.c_str(), c.size());
    
            for (int i = 0; i < name[i] != '\0'; i++) {
                std::string firstChar   = getString(name[i]);
                std::string secondChar  = getString(name[(i + 1)]);

                if (map.find(firstChar) != map.end()) {
                    if (map[firstChar].find(secondChar) != map[firstChar].end()) {
                        double mapValue             = map[firstChar][secondChar];
                        mapValue                   += 1;

                        map[firstChar][secondChar]  = mapValue;
                    }
                }
            }
        }

        for (int i = 0; i < m_cAlphabet[i] != '\0'; i++) {
            std::string firstChar = getString(m_cAlphabet[i]);

            double total = 0;
            if (map.find(firstChar) != map.end()) {
                for (std::map<std::string, double>::iterator i = map[firstChar].begin(); i != map[firstChar].end(); ++i) {
                    std::string secondChar = i->first;
                    
                    if (map[firstChar].find(secondChar) != map[firstChar].end()) {
                        total += map[firstChar][secondChar];
                    }
                }
            }

            for (int j = 0; j < m_cAlphabet[j] != '\0'; j++) {
                std::string secondChar      = getString(m_cAlphabet[j]);
                double mapValue             = (map[firstChar][secondChar] / total);
                map[firstChar][secondChar]  = mapValue;
            }
        }

        m_mLetterToLetterChance = map;
    }

    std::map<std::string, double> Markov::getAlphabetMap() {
        std::map<std::string, double> map;
        
        double d = 0;
        for (int i = 0; i < m_cAlphabet[i] != '\0'; i++) {
            std::string s   = getString(m_cAlphabet[i]);
            map[s]          = d;
        }

        return map;
    }

    Markov::~Markov() {
    }
};
