#ifndef NordicArts_Game_Names_H
#define NordicArts_Game_Names_H

#include <boost/locale.hpp>

#include "../Includes.hpp"

#include <NordicOS/OS.hpp>
#include <NordicOS/Logger/Logger.hpp>
#include <NordicOS/Time/Time.hpp>

namespace NordicArts {
    namespace GameNS {
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

                NordicOS::Logger      *m_pLogger = nullptr;;

            // Methods
            public:
                Names(NordicOS::Logger *pLogger);
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
};


#endif
