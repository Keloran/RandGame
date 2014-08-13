#include "./Species.hpp"

namespace NordicArts {
    Species::Species() {
        loadSpecies();
    }

    void Species::loadSpecies() {
        int iRand   = 0;
        int i       = 0;

        boost::property_tree::ptree pTree;
        boost::property_tree::read_json("./GameFiles/Trees/trees.json", pTree);
        BOOST_FOREACH(boost::property_tree::ptree::value_type &trees, pTree.get_child("trees")) {
            std::string cName           = trees.second.get<std::string>("name");
            
            int iMaxSize                = trees.second.get<int>("maxSize");
    
            TreeSpecies sSpecies        = TreeSpecies(cName);
            sSpecies.cLeafType          = trees.second.get<std::string>("leafType");
            sSpecies.cSeedType          = trees.second.get<std::string>("seedType");

            sSpecies.fGrowthRate        = trees.second.get<float>("growthRate");
            sSpecies.fSeedRate          = trees.second.get<float>("seedRate");    

            sSpecies.iMaxHeight         = trees.second.get<int>("maxHeight");
            sSpecies.iMaxWidth          = trees.second.get<int>("maxWidth");
            sSpecies.iMaxSize           = trees.second.get<int>("maxSize");
            sSpecies.iSeedSurvability   = trees.second.get<int>("seedSurvivability");
            sSpecies.iSeedSpread        = trees.second.get<int>("seedSpread");
            sSpecies.iSlopeThreshold    = trees.second.get<int>("slopeThreshold");
            
            // Random inital size
            Time::Time oTime;
            Time::Time *pTime = &oTime;
            srand(pTime->getNanoSeconds());
            int iRand = (rand() % iMaxSize);
           
            sSpecies.iInitialSize   = iRand;
            sSpecies.iSpecies       = i;
            
            m_vTrees.insert(m_vTrees.begin(), sSpecies);
            i++;
        }
    }

    std::vector<TreeSpecies> Species::getSpecies() {
        return m_vTrees;
    }
};
