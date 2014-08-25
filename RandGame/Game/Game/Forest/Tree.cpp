#include "./Tree.hpp"

namespace NordicArts {
    namespace GameNS {
        Tree::Tree() : m_sSpecies(nullptr) {
        }

        Tree::Tree(TreeSpecies sSpecies, int iX, int iY) : m_iX(iX), m_iY(iY), m_sSpecies(sSpecies), m_iSize(sSpecies.iInitialSize) {
        }

        void Tree::absorb(Tree oVictim) {
            m_iSize = std::min((iGetSize() + int(oVictim.fGetSize())), iGetSize());
        }

        void Tree::grow() {
            m_iSize = std::min((iGetSize() + int(m_sSpecies.fGrowthRate)), m_sSpecies.iMaxSize);
        }

        void Tree::setTree(int iTree) {
            m_iTree = iTree;
        }

        bool Tree::overLapping(Tree oOther) {
            float fOverLap = std::sqrt(std::pow(oOther.getX() - getX(), 2) + std::pow(oOther.getY() - getY(), 2));

            return (fOverLap <= (oOther.fGetSize() + fGetSize()));
        }

        bool Tree::isMature() {
            return (iGetSize() == m_sSpecies.iMaxSize);
        }

        bool Tree::containsPoint(int iX, int iY) {
            float fPoint = std::sqrt(std::pow((getX() - iX), 2) + std::pow((getY() - iY), 2));

            return (fPoint <= fGetSize());
        }

        bool Tree::smallerThan(Tree oOther) {
            return (iGetSize() < oOther.iGetSize());
        }

        int Tree::iGetSize() const {
            return m_iSize;
        }

        float Tree::fGetSize() const {
            return m_fSize;
        }

        int Tree::getX() const {
            return m_iX;
        }

        int Tree::getY() const {
            return m_iY;
        }

        int Tree::getTree() const {
            return m_iTree;
        }
    };
};
