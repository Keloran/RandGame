#ifndef NORDICARTS_OS_STRING_INLINE
#define NORDICARTS_OS_STRING_INLINE

#include "../ExceptionHandler/ExceptionHandler.hpp"

template<typename T>
T convertToType(const std::string &cString, std::ios_base &(*pFormat)(std::ios_base&)) {
    T output;

    std::istringstream input(cString);
    input >> pFormat >> output;

    if (!input) {
        std::ostringstream cStream;
        cStream << __FUNCTION__ << ": Bad conversion of [" << cString << "] to " << typeid(output).name();
        throw NordicArts::NordicOS::ExceptionHandler::ExceptionHandler(cStream);
    }    

    char cChar;
    if (input.get(cChar)) {
        std::ostringstream cStream;
        cStream << __FUNCTION__ << ": Conversion of [" << cString << "] to " << typeid(output).name() << " - [" << output << "] Failed";
        
        throw NordicArts::NordicOS::ExceptionHandler::ExceptionHandler(cStream);
    }

    return output;
}

#endif
