#ifndef NordicArts_Game_Forest_Tree_H
#define NordicArts_Game_Forest_Tree_H

#include <NordicOS/OS.hpp>
#include "../Includes.hpp"
#include "./Species.hpp"

namespace NordicArts {
    namespace GameNS {
        class Tree {
        // Variables
        public:
        protected:
        private:
            int m_iSize;
            int m_iX;
            int m_iY;
            int m_iTree;

            float m_fSize;

            TreeSpecies m_sSpecies;

        // Methods
        public:
            Tree();
            Tree(TreeSpecies sSpecies, int iX, int iY);

            int iGetSize() const;
            float fGetSize() const;

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
};

#endif
