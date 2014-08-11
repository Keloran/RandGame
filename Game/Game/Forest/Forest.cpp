#include "./Forest.hpp"

namespace NordicArts {
    Forest::Forest(int iRandomSeed, int iWidth, int iHeight) : m_iHeight(iHeight), m_iWidth(iWidth), m_iCellSize(10) {            
        std::map<int, int> aCells;
            
        int maxLength = std::ceil(getHeight() / getSize());
        for (int i = 0; i < maxLength; i++) {
            
        }
    }

    void Forest::addTree(Tree oTree) {
        m_vTrees.insert(m_vTrees.begin(), oTree);
        
        //std::map<std::map<int, int>, Tree> mCell = getCell(oTree);
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

};
