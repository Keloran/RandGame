#ifndef MARKOV_HEADER
#define MARKOV_HEADER

#include <boost/locale.hpp>

#include "../../includes.h"
#include "../../Tools/Strng/Strng.h"

namespace NordicArts {
    class Markov {
        // Variables
        public:
        protected:
        private:
            std::map<std::string, double> m_mFirstLetterChance;
            std::map<std::string, double> m_mLastLetterChance;

            std::map<std::string, std::map<std::string, double> > m_mLetterToLetterChance;
            
            std::vector<std::string> m_vNames;

            char m_cAlphabet[28]    = "abcdefghijklmnopqrstuvqwxyz";
            float m_fVariance       = 0.0f;

        // Methods
        public:
            Markov(); 
            virtual ~Markov();

            std::string generateWord();
            
            void setVariance(float fVariance);

        protected:
        private:     
            void fillNameList();
            void generateFirstLetterMap();
            void generateLastLetterMap();
            void generateLetterToLetterMap();

            std::map<std::string, double> getAlphabetMap();
    
            std::locale m_pLocale;
    };
};

#endif
