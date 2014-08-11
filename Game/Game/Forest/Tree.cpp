#include "./Tree.hpp"

namespace NordicArts {
    Tree::Tree(Species sSpecies, int iX, int iY) : m_iX(iX), m_iY(iY), m_sSpecies(sSpecies), m_fSize(sSpecies.fInitialSize) {
    }

    void Tree::absorb(Tree oVictim) {
        m_fSize = std::min((getSize() + oVictim.getSize()), getSize());
    }

    void Tree::grow() {
        m_fSize = std::min((getSize() + m_sSpecies.fGrowthRate), m_sSpecies.fMaxSize);
    }

    bool Tree::overLapping(Tree oOther) {
        float fOverLap = std::sqrt(std::pow(oOther.getX() - getX(), 2) + std::pow(oOther.getY() - getY(), 2));
        
        return (fOverLap <= (oOther.getSize() + getSize()));
    }

    bool Tree::isMature() {
        return (getSize() == m_sSpecies.fMaxSize);
    }

    bool Tree::containsPoint(int iX, int iY) {
        float fPoint = std::sqrt(std::pow((getX() - iX), 2) + std::pow((getY() - iY), 2));

        return (fPoint <= getSize());
    }

    bool Tree::smallerThan(Tree oOther) {
        return (getSize() < oOther.getSize());
    }

    float Tree::getSize() const {
        return m_fSize;
    }
    
    int Tree::getX() const {
        return m_iX;
    }

    int Tree::getY() const {
        return m_iY;
    }
};
