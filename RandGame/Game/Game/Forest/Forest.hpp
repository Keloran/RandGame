#ifndef NORDICARTS_GAME_FOREST_H
#define NORDICARTS_GAME_FOREST_H

#include <NordicOS/OS.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>

#include "../Includes.hpp"
#include "./Tree.hpp"

namespace NordicArts {
    namespace GameNS {
        class Forest {
            // Variables
            public:
            protected:
            private:
                std::vector<Tree> m_vTrees;

                std::map<int, std::map<int, std::vector<Tree>>> m_mCells;

                int m_iWidth;
                int m_iHeight;
                int m_iCellSize;
                int m_iMaxWidth;
                int m_iMaxHeight;

            // Methods
            public:
                Forest(int iRandomSeed, int iWidth, int iHeight);

                void addTree(Tree oTree);
                void removeTree(Tree oTree);
                void iterate();

                std::vector<Tree> spreadTreeSeed(Tree oTree);

                std::map<int, std::map<int, std::vector<Tree>>> getAllBoringCellsByPoint(int iX, int iY);
                std::vector<Tree> getAllBoringCellsByTree(Tree oTree);
                std::vector<Tree> getCellFromPoint(int iX, int iY);
                std::vector<Tree> getCell(Tree oTree);

                int getHeight() const;
                int getMaxHeight() const;
                int getWidth() const;
                int getMaxWidth() const;
                int getSize() const;

            protected:
            private:
                bool canPlantSeed(int iX, int iY, Species sSpecies);
                bool isPointTooCloseToTree(int iX, int iY, Species sSpecies);
                bool isPointInTree(int iX, int iY);
        };
    };
};

#endif
