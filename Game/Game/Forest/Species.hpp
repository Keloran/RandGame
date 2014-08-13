#ifndef NORDICARTS_GAME_FOREST_SPECIES_H
#define NORDICARTS_GAME_FOREST_SPECIES_H

#include <NordicOS/OS.hpp>
#include <NordicOS/FileHandler/TextFileReader/TextFileReader.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "../Includes.hpp"

namespace NordicArts {
    struct TreeSpecies {
        std::string cName;
        std::string cLeafType;
        std::string cSeedType;

        float fGrowthRate;
        float fSeedRate;

        int iMaxHeight;
        int iMaxWidth;
        int iMaxSize;
        int iSeedSurvability;
        int iSeedSpread;
        int iSeedRate;
        int iSlopeThreshold;        
        int iInitialSize;
        int iSpecies;

        TreeSpecies(std::string cNameIn) : cName(cNameIn) {}
    };

    class Species {
        // Variables
        public:           
        protected:
        private:
            std::vector<TreeSpecies> m_vTrees;

        // Methods
        public:
            Species();
            
            std::vector<TreeSpecies> getSpecies();

        protected:
        private:
            void loadSpecies();

    };
};

#endif
