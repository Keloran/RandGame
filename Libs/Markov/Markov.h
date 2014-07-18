#ifndef MARKOV_HEADER
#define MARKOV_HEADER

#include <map>
#include <string>

namespace NordicArts {
    class Markov {
        // Variables
        public:
        protected:
        private:
            std::map<std::string, double> m_firstLetterChance;
            std::map<std::string, double> m_lastLetterChance;
            std::map<std::string, std::map<std::string, double> > m_letterToLetterChance;

            char *m_alphabet; 

        // Methods
        public:
            Markov(); 

        protected:
        private:     
            std::string generateWord();
            std::string fill   

    };
};

#endif
