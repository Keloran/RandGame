#ifndef NordicArts_NordicOS_ExceptionHandler_H
#define NordicArts_NordicOS_ExceptionHandler_H

#include "../OS.hpp"

namespace NordicArts {
    namespace NordicOS {        
        class ExceptionHandler final {
        // Variables
        public:
            ExceptionHandler    *m_pSingleton;

        protected:
        private:
            std::string          m_cMessage;

        // Methods
        public:
            explicit ExceptionHandler(const std::string &cMessage, bool bSaveToFile = true);
            explicit ExceptionHandler(const std::ostringstream &cMessage, bool bSaveToFile = true);

            const std::string &getMessage() const;

        protected:
        private:
            ExceptionHandler &operator=(const ExceptionHandler &cConst);
        };
    };
};

#endif
