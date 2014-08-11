#include "./Forest.hpp"

namespace NordicArts {
    Forest::Forest(int iRandomSeed, int iWidth, int iHeight) : m_iHeight(iHeight), m_iWidth(iWidth), m_iCellSize(10) {            
        std::map<int, std::map<int, std::vector<Tree>>> aCells;
            
        m_iMaxHeight   = std::ceil(getHeight() / getSize());
        m_iMaxWidth    = std::ceil(getWidth() / getSize());
    }

    void Forest::addTree(Tree oTree) {
        int iTree = m_vTrees = m_vTrees.end();
        oTree.setTree(iTree);

        m_vTrees.insert(iTree, oTree);
        
        std::vector<Tree> mCell = getCell(oTree);
        mCell.insert(mCell.end(), oTree);
    }

    void Forest::removeTree(Tree oTree) {
        for (int it = m_vTrees.begin(); it != m_vTrees.end(); it++) {
            if (it == oTree.getTree()) {
                m_vTrees.erase(oTree.getTree());
            }
        }

        std::vector<Tree> mCell = getCell(oTree);
        for (int it = mCell.begin(); it != mCell.end(); it++) {
            if (it == oTree.getTree()) {
                mCell.erase(oTree.getTree());
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
        return getAllBoringCellsByPoint(oTree.getX(), oTree.getY());
    }

    std::vector<Tree> Forest::getAllBoringCellsByPoint(int iX, int iY) {
        
    }
};
