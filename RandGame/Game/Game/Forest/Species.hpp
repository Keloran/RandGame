#ifndef NordicArts_Game_Forest_Species_H
#define NordicArts_Game_Forest_Species_H

#include <NordicOS/OS.hpp>
#include <NordicOS/FileHandler/TextFileReader/TextFileReader.hpp>
#include <NordicOS/Time/Time.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "../Includes.hpp"

namespace NordicArts {
    namespace GameNS {
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
};

#endif
