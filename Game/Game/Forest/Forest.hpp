#ifndef NORDICARTS_GAME_FOREST_H
#define NORDICARTS_GAME_FOREST_H

#include <NordicOS/OS.hpp>

#include "../Includes.hpp"
#include "./Tree.hpp"

namespace NordicArts {
    class Forest {
        // Variables
        public:
        protected:
        private:
            std::list<Tree> m_lTrees;

            std::map<std::map<int, int>, Tree> m_mCells;
            
            int m_iWidth;
            int m_iHeight;
            int m_iCellSize;
            

        // Methods
        public:
            Forest(int iRandomSeed, int iWidth, int iHeight);

            void addTree(Tree oTree);
            void removeTree(Tree oTree);
            void iterate();

            std::list<Tree> spreadTreeSeed(Tree oTree);
        
            std::map<std::map<int, int>, Tree> getAllBoringCellsByPoint(int iX, int iY);
            std::map<std::map<int, int>, Tree> getAllBoringCellsByTree(Tree oTree);
            std::map<std::map<int, int>, Tree> getCellFromPoint(int iX, int iY);
            std::map<std::map<int, int>, Tree> getCell(Tree oTree);

            int getHeight() const;
            int getWidth() const;
            int getSize() const;

        protected:
        private:
            bool canPlantSeed(int iX, int iY, Species sSpecies);
            bool isPointTooCloseToTree(int iX, int iY, Species sSpecies);
            bool isPointInTree(int iX, int iY);

    };
};

#endif
