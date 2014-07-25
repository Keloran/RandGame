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

            char m_aAlphabet[28] = "abcdefghijklmnopqrstuvqwxyz";
            //char m_aAlphabet[26];

        // Methods
        public:
            Markov(); 
            virtual ~Markov();
            std::string generateWord();

        protected:
        private:     
            std::string getString(char c);

            void fillNameList();

            std::map<std::string, double> generateFirstLetterMap();
            std::map<std::string, double> generateLastLetterMap();
            std::map<std::string, std::map<std::string, double> > generateLetterToLetterMap();
            std::map<std::string, double> getAlphabetMap();
    };
};

#endif
