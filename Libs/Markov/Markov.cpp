#include "./Markov.h"

namespace NordicArts {
    Markov::Markov() {
        fillNameList();
    }

    void Markov::fillNameList() {
        std::vector<std::string> names;

        std::ifstream inFile("./Extras/names");
        std::string cLine;

        while (std::getline(inFile, cLine)) {
            cLine = boost::locale::to_lower(cLine);
            names.push_back(cLine);
        }

        std::cout << "Length: " << names.size() << std::endl;
    }

    Markov::~Markov() {
    }
};
