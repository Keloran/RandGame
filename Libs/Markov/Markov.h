#ifndef MARKOV_HEADER
#define MARKOV_HEADER

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <boost/locale.hpp>

#include "../../includes.h"

namespace NordicArts {
    class Markov {
        // Variables
        public:
        protected:
        private:
            std::map<std::string, double> m_firstLetterChance;
            std::map<std::string, double> m_lastLetterChance;
            std::map<std::string, std::map<std::string, double> > m_letterToLetterChance;
            std::vector<std::string> m_vNames;

            const char *m_alphabet = "abcdefghijklmnopqrstuvqwxyz";

        // Methods
        public:
            Markov(); 
            virtual ~Markov();

        protected:
        private:     
            std::string generateWord();
            void fillNameList();

    };
};

#endif
