#ifndef NORDICARTS_GAME_TREE_H
#define NORDICARTS_GAME_TREE_H

#include <NordicOS/OS.hpp>
#include "../Includes.hpp"

namespace NordicArts {
    struct Species {
        std::string cName;
        
        float fGrowthRate;
        float fMaxSize;
        float fSeedSurvability;
        float fSeedSpreadDistance;
        float fSeedRate;
        float fSlopeThreshhold;
        float fInitialSize;

        Species(std::string cNameIn, float fGrowthRateIn) : cName(cNameIn), fGrowthRate(fGrowthRateIn) {}
    };

    class Tree {
        // Variables
        public:
        protected:
        private:
            float m_fSize;

            int m_iX;
            int m_iY;

            int m_iTree;
            
            Species m_sSpecies;
        
        // Methods
        public:
            Tree(Species sSpecies, int iX, int iY);

            float getSize() const;

            int getX() const;
            int getY() const;
            int getTree() const;

            void absorb(Tree oVictim);
            void grow();
            void setTree(int iTree);

            bool overLapping(Tree oOther);
            bool containsPoint(int iX, int iY);
            bool smallerThan(Tree oOther);
            bool isMature();

        protected:
        private:

    };
};

#endif
