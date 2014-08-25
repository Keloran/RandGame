#include "./Forest.hpp"

namespace NordicArts {
    namespace GameNS {
        Forest::Forest(int iRandomSeed, int iWidth, int iHeight) : m_iHeight(iHeight), m_iWidth(iWidth), m_iCellSize(10) {
            std::map<int, std::map<int, std::vector<Tree>>> aCells;

            m_iMaxHeight   = std::ceil(getHeight() / getSize());
            m_iMaxWidth    = std::ceil(getWidth() / getSize());
        }

        void Forest::addTree(Tree oTree) {
            int iTree = m_vTrees.size();
            oTree.setTree(iTree);

            m_vTrees.insert(m_vTrees.end(), oTree);

            std::vector<Tree> mCell = getCell(oTree);
            mCell.insert(mCell.end(), oTree);
        }

        void Forest::removeTree(Tree oTree) {
            for (std::vector<Tree>::iterator it = m_vTrees.begin(); it != m_vTrees.end(); it++) {
                if (it->getTree() == oTree.getTree()) {
                    m_vTrees.erase(it);
                }
            }

            std::vector<Tree> mCell = getCell(oTree);
            for (std::vector<Tree>::iterator it = mCell.begin(); it != mCell.end(); it++) {
                if (it->getTree() == oTree.getTree()) {
                    mCell.erase(it);
                }
            }
        }

        int Forest::getHeight() const {
            return m_iHeight;
        }
        int Forest::getWidth() const {
            return m_iWidth;
        }
        int Forest::getSize() const {
            return m_iCellSize;
        }

        std::vector<Tree> Forest::getCell(Tree oTree) {
            return getCellFromPoint(oTree.getX(), oTree.getY());
        }

        std::vector<Tree> Forest::getCellFromPoint(int iX, int iY) {
            int iCol = (int)(iX / getSize());
            int iRow = (int)(iY / getSize());

            return m_mCells[iRow][iCol];
        }

        std::vector<Tree> Forest::getAllBoringCellsByTree(Tree oTree) {
            std::vector<Tree> ret;
            return ret;

            //return getAllBoringCellsByPoint(oTree.getX(), oTree.getY());
        }

        std::map<int, std::map<int, std::vector<Tree>>> Forest::getAllBoringCellsByPoint(int iX, int iY) {
            int iCol = (int)(iX / getSize());
            int iRow = (int)(iY / getSize());

            // X Range
            std::vector<int> vX;
            boost::push_back(vX, boost::irange(-1, 2));

            // Y Range
            std::vector<int> vY;
            boost::push_back(vY, boost::irange(-1, 2));

            Species::Species oSpecies;

            for (std::vector<int>::iterator itX = vX.begin(); itX != vX.end(); itX++) {
                for (std::vector<int>::iterator itY = vY.begin(); itY != vY.end(); itY++) {
                    if (((iRow + *itX) >= 0) && ((iRow + *itX) < m_mCells.size()) && ((iCol + *itY) >= 0) && ((iCol + *itY) < m_mCells[0].size())) {
                        //m_mCells.insert(m_mCells.end(), m_mCells[iRow + *itX][iCol + *itY]);
                    }
                }
            }

            return m_mCells;
        }
    };
};
