#include "./Markov.h"

namespace NordicArts {
    Markov::Markov() {
        fillNameList();
    }

    void Markov::fillNameList() {
        std::vector<std::string> names;

        std::ifstream inFile("./Extras/names");
        std::string cLine;

        std::locale locale = boost::locale::generator().generate("en_US.UTF-8");

        while (std::getline(inFile, cLine)) {
            cLine = boost::locale::to_lower(cLine, locale);
            names.push_back(cLine);
        }

        std::cout << "Length: " << names.size() << std::endl;
    }

    Markov::~Markov() {
    }
};
