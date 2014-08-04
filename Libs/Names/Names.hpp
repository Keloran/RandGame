#ifndef NORDICARTS_NAMES_H
#define NORDICARTS_NAMES_H

#include <boost/locale.hpp>

#include "../../includes.hpp"
#include "../Tools/OS/OS.hpp"

namespace NordicArts {
    class Names {
        // Variables
        public:
        protected:
        private:
            bool m_bDebug;

            std::vector<std::string> m_vPrefixes;
            std::vector<std::string> m_vStems;
            std::vector<std::string> m_vSuffixes;

            std::locale m_pLocale;

            Logger      *m_pLogger = nullptr;;

        // Methods
        public:
            Names(Logger *pLogger);
            Names();
            virtual ~Names();

            std::string generateName();

        protected:
        private:
            void init();

            void fillPrefixes();
            void fillStems();
            void fillSuffixes();
    };
};


#endif
