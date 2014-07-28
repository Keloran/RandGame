#ifndef NORDICARTS_NAMES_H
#define NORDICARTS_NAMES_H

#include <boost/locale.hpp>

#include "../../includes.h"
#include "../../Tools/Strng/Strng.h"

namespace NordicArts {
    class Names {
        // Variables
        public:
        protected:
        private:
            std::vector<std::string> m_vPrefixes;
            std::vector<std::string> m_vStems;
            std::vector<std::string> m_vSuffixes;

        // Methods
        public:
            Names();
            virtual ~Names();

            std::string generateName();

        protected:
        private:
            void fillPrefixes();
            void fillStems();
            void fillSuffixes();
    };
};


#endif
