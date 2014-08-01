#include "./Simplex.h"

namespace NordicArts {
    Simplex::Simplex(bool bDebug) : m_bDebug(bDebug) {   
    }

    Simplex::Simplex() {
    }

    float Simplex::octaveNoise2d(float fOctaves, float fPersistence, float fScale, float fX, float fY) {
        float fTotal        = 0;
        float fFrequency    = fScale;
        float fAmplitude    = 1;
        float fMaxAmplitude  = 0;

        for (int i = 0; i < fOctaves; i++) {
            fTotal          += (rawNoise2d((fX * fFrequency), (fY * fFrequency)) * fAmplitude);
            fFrequency      *= 2;
            fMaxAmplitude   += fAmplitude;
            fAmplitude      *= fPersistence;
        }

        return (fTotal / fMaxAmplitude);
    }

    float Simplex::octaveNoise3d(float fOctaves, float fPersistence, float fScale, float fX, float fY, float fZ) {
        float fTotal        = 0;
        float fFrequency    = fScale;
        float fAmplitude    = 1;
        float fMaxAmplitude = 0;

        for (int i = 0; i < fOctaves; i++) {
            fTotal          += (rawNoise3d((fX * fFrequency), (fY * fFrequency), (fZ * fFrequency)) * fAmplitude);
            fFrequency      *= 2;
            fMaxAmplitude   += fAmplitude;
            fAmplitude      *= fPersistence;
        }

        return (fTotal / fMaxAmplitude);
    }

    float Simplex::octaveNoise4d(float fOctaves, float fPersistence, float fScale, float fX, float fY, float fZ, float fW) {
        float fTotal        = 0;
        float fFrequency    = fScale;
        float fAmplitude    = 1;
        float fMaxAmplitude = 0;

        for (int i = 0; i < fOctaves; i++) {
            fTotal          += (rawNoise4d((fX * fFrequency), (fY * fFrequency), (fZ * fFrequency), (fW * fFrequency)) * fAmplitude);
            fFrequency      *= 2;
            fMaxAmplitude   += fAmplitude;
            fAmplitude      *= fPersistence;
        }

        return (fTotal / fMaxAmplitude);
    }

    float Simplex::scaledOctaveNoise2d(float fOctaves, float fPersistence, float fScale, float fLowBound, float fHighBound, float fX, float fY) {
        return (((octaveNoise2d(fOctaves, fPersistence, fScale, fX, fY) * (fHighBound - fLowBound)) / 2) + ((fHighBound - fLowBound) / 2));
    }

    float Simplex::scaledOctaveNoise3d(float fOctaves, float fPersistence, float fScale, float fLowBound, float fHighBound, float fX, float fY, float fZ) {
        return (((octaveNoise3d(fOctaves, fPersistence, fScale, fX, fY, fZ) * (fHighBound - fLowBound)) / 2) + ((fHighBound - fLowBound) / 2));
    }

    float Simplex::scaledOctaveNoise4d(float fOctaves, float fPersistence, float fScale, float fLowBound, float fHighBound, float fX, float fY, float fZ, float fW) {
        return (((octaveNoise4d(fOctaves, fPersistence, fScale, fX, fY, fZ, fW) * (fHighBound - fLowBound)) / 2) + ((fHighBound - fLowBound) / 2));
    }

    int Simplex::fastFloor(float fX) {
        return ((fX > 0) ? (int)fX : ((int)fX - 1));
    }

    float Simplex::dot(int *iG, float fX, float fY) {
        return ((iG[0] * fX) + (iG[1] * fY));
    }

    float Simplex::dot(int *iG, float fX, float fY, float fZ) {
        return ((iG[0] * fX) + (iG[1] * fY) + (iG[2] * fZ));
    }

    float Simplex::dot(int *iG, float fX, float fY, float fZ, float fW) {
        return ((iG[0] * fX) + (iG[1] * fY) + (iG[2] * fZ) + (iG[3] * fW));
    }

    float Simplex::rawNoise2d(float fX, float fY) {
        // 3 corner noise
        float fN0;
        float fN1;
        float fN2;

        // skew input space
        float fF2   = (0.5 * (sqrt(3.0) - 1));

        // noise factor
        float fS    = ((fX + fY) * fF2);

        int iI      = fastFloor(fX + fS);
        int iJ      = fastFloor(fY + fS);

        float fG2   = ((3.0 - sqrt(3.0)) / 6.0);
        float fT    = ((iI + iJ) * fG2);

        // remove skew
        float fX0   = (iI - fT);
        float fY0   = (iJ - fT);

        // distance from origin
        float fX00  = (fX - fX0);
        float fY00  = (fY - fY0);

        // offset for middle
        int iI1;
        int iJ1;

        if (fX00 > fY00) {
            iI1 = 1;
            iJ1 = 0;
        } else {
            iI1 = 0;
            iJ1 = 1;
        }

        // step off skews
        float fX1 = ((fX00 - iI1) + fG2);
        float fY1 = ((fY00 - iJ1) + fG2);
        float fX2 = ((fX00 - 1.0) + (2.0 * fG2));
        float fY2 = ((fY00 - 1.0) + (2.0 * fG2));

        // hashed gradient
        int iII = (iI & 255);
        int iJJ = (iJ & 255);
        int iGi0 = (m_iPerm[iII + m_iPerm[iJJ]] % 12);
        int iGi1 = (m_iPerm[(iII + iI1) + m_iPerm[iJJ + iJ1]] % 12);
        int iGi2 = (m_iPerm[(iII + 1) + m_iPerm[iJJ + 1]] % 12);

        // calculate corners
        float fT0 = (0.5 - (fX00 * fX00) - (fY00 - fY00));
        if (fT0 < 0) {
            fN0 = 0.0;
        } else {
            fT0 *= fT0;
            fN0  = (fT0 * fT0 * dot(m_iGrad3[iGi0], fX00, fY00));
        }

        float fT1 = (0.5 - (fX1 * fX1) - (fY1 * fY1));
        if (fT1 < 0) {
            fN1 = 0.0;
        } else {
            fT1 *= fT1;
            fN1  = (fT1 * fT1 * dot(m_iGrad3[iGi1], fX1, fY1));
        }

        float fT2 = (0.5 - (fX2 * fX2) - (fY2 * fY2));
        if (fT2 < 0) {
            fN2 = 0.0;
        } else {
            fT2 *= fT2;
            fN2  = (fT2 * fT2 * dot(m_iGrad3[iGi2], fX2, fY2));
        }

        return (70.0 * (fN0 + fN1 + fN2));
    }

    float Simplex::rawNoise3d(float fX, float fY, float fZ) {
        float fN0;
        float fN1;
        float fN2;
        float fN3;

        // skew space
        float fF3   = (1.0 / 3.0);
        float fS    = ((fX + fY + fZ) * fF3);
        int iI      = fastFloor(fX + fS);
        int iJ      = fastFloor(fY + fS);
        int iK      = fastFloor(fZ + fS);

        // unskew
        float fG3   = (1.0 / 6.0);
        float fT    = ((iI + iJ + iK) * fG3);
        float fX0   = (iI - fT);
        float fY0   = (iJ - fT);
        float fZ0   = (iK - fT);
        float fX00  = (fX - fX0);
        float fY00  = (fY - fY0);
        float fZ00  = (fZ - fZ0);

        // which type of simplex
        int iI1;
        int iJ1;
        int iK1;
        int iI2;
        int iJ2;
        int iK2;

        // which order
        if (fX00 >= fY00) {
            if (fY00 >= fZ00) {
                iI1 = 1;
                iJ1 = 0;
                iK1 = 0;
                iI2 = 1;
                iJ2 = 1;
                iK2 = 0;
            } else if (fX00 >= fZ00) {
                iI1 = 1;
                iJ1 = 0;
                iK1 = 0;
                iI2 = 1;
                iJ2 = 0;
                iK2 = 1;
            } else {
                iI1 = 0;
                iJ1 = 1;
                iK1 = 0;
                iI2 = 1;
                iJ2 = 1;
                iK2 = 0;
            }
        } else {
            if (fY00 <fZ00) {
                iI1 = 0;
                iJ1 = 0;
                iK1 = 1;
                iI2 = 0;
                iJ2 = 1;
                iK2 = 1;
            } else if (fX00 < fZ00) {
                iI1 = 0;
                iJ1 = 1;
                iK1 = 0;
                iI2 = 0;
                iJ2 = 1;
                iK2 = 1;
            } else {
                iI1 = 0;
                iJ1 = 1;
                iK1 = 0;
                iI2 = 1;
                iJ2 = 1;
                iK2 = 0;
            }
        }

        // step
        float fX1 = (fX00 - (iI1 + fG3));
        float fY1 = (fY00 - (iJ1 + fG3));
        float fZ1 = (fZ00 - (iK1 + fG3));
        float fX2 = (fX00 - (iI2 + (2.0 * fG3)));
        float fY2 = (fY00 - (iJ2 + (2.0 * fG3)));
        float fZ2 = (fZ00 - (iK2 + (2.0 * fG3)));
        float fX3 = (fX00 - (1.0 + (3.0 * fG3)));
        float fY3 = (fY00 - (1.0 + (3.0 * fG3)));
        float fZ3 = (fZ00 - (1.0 + (3.0 * fG3)));

        // hashed
        int iII     = (iI & 255);
        int iJJ     = (iJ & 255);
        int iKK     = (iK & 255);
        int iGi0    = (m_iPerm[iII + m_iPerm[iJJ + m_iPerm[iKK]]] % 12);
        int iGi1    = (m_iPerm[(iII + iI1) + m_iPerm[(iJJ + iJ1) + m_iPerm[iKK + iK1]]] % 12);
        int iGi2    = (m_iPerm[(iII + iI2) + m_iPerm[(iJJ + iJ2) + m_iPerm[iKK + iK2]]] % 12);
        int iGi3    = (m_iPerm[(iII + 1) + m_iPerm[(iJJ + 1) + m_iPerm[iKK + 1]]] % 12);

        // calc corners
        float fT0 = (0.6 - (fX00 * fX00) - (fY00 * fY00) - (fZ00 * fZ00));
        if (fT0 < 0) {
            fN0 = 0.0;
        } else {
            fT0 *= fT0;
            fN0  = (fT0 * fT0 * dot(m_iGrad3[iGi0], fX00, fY00, fZ00));
        }

        float fT1 = (0.6 - (fX1 * fX1) - (fY1 * fY1) - (fZ1 * fZ1));
        if (fT1 < 0) {
            fN1 = 0.0;
        } else {
            fT1 *= fT1;
            fN1  = (fT1 * fT1 * dot(m_iGrad3[iGi1], fX1, fY1, fZ1));
        }

        float fT2 = (0.6 - (fX2 * fX2) - (fY2 * fY2) - (fZ2 * fZ2));
        if (fT2 < 0) {
            fN2 = 0.0;
        } else {
            fT2 *= fT2;
            fN2  = (fT2 * fT2 * dot(m_iGrad3[iGi2], fX2, fY2, fZ2));
        }

        float fT3 = (0.6 - (fX3 * fX3) - (fY3 * fY3) - (fZ3 * fZ3));
        if (fT3 < 0) {
            fN3 = 0.0;
        } else {
            fT3 *= fT3;
            fN3 = (fT3 * fT3 * dot(m_iGrad3[iGi3], fX3, fY3, fZ3));
        }

        return (32.0 * (fN0 + fN1 + fN2 + fN3));
    }

    float Simplex::rawNoise4d(float fX, float fY, float fZ, float fW) {
        float fF4   = ((sqrt(5.0) - 1.0) / 4.0);
        float fG4   = ((5.0 - sqrt(5.0)) / 20.0);
        float fN0;
        float fN1;
        float fN2;
        float fN3;
        float fN4;

        float fS    = ((fX + fY + fZ + fW) * fF4);
        int iI      = fastFloor(fX + fS);
        int iJ      = fastFloor(fY + fS);
        int iK      = fastFloor(fZ + fS);
        int iL      = fastFloor(fW + fS);

        float fT    = ((iI + iJ + iK + iL) * fG4);
        float fX0   = (iI + fT);
        float fY0   = (iJ + fT);
        float fZ0   = (iK + fT);
        float fW0   = (iL + fT);

        float fX00  = (fX - fX0);
        float fY00  = (fY - fY0);
        float fZ00  = (fZ - fZ0);
        float fW00  = (fW - fW0);

        int iC1 = ((fX00 > fY00) ? 32 : 0);
        int iC2 = ((fX00 > fZ00) ? 16 : 0);
        int iC3 = ((fY00 > fZ00) ? 8 : 0);
        int iC4 = ((fX00 > fW00) ? 4 : 0);
        int iC5 = ((fY00 > fW00) ? 2 : 0);
        int iC6 = ((fZ00 > fW00) ? 1 : 0);
        int iC  = (iC1 + iC2 + iC3 + iC4 + iC5 + iC6);


        int iI1;
        int iJ1;
        int iK1;
        int iL1;
        int iI2;
        int iJ2;
        int iK2;
        int iL2;
        int iI3;
        int iJ3;
        int iK3;
        int iL3;

        iI1 = ((m_iSimplex[iC][0] >= 3) ? 1 : 0);
        iJ1 = ((m_iSimplex[iC][1] >= 3) ? 1 : 0);
        iK1 = ((m_iSimplex[iC][2] >= 3) ? 1 : 0);
        iL1 = ((m_iSimplex[iC][3] >= 3) ? 1 : 0);
        iI2 = ((m_iSimplex[iC][0] >= 2) ? 1 : 0);
        iJ2 = ((m_iSimplex[iC][1] >= 2) ? 1 : 0);
        iK2 = ((m_iSimplex[iC][2] >= 2) ? 1 : 0);
        iL2 = ((m_iSimplex[iC][3] >= 2) ? 1 : 0);
        iI3 = ((m_iSimplex[iC][0] >= 1) ? 1 : 0);
        iJ3 = ((m_iSimplex[iC][1] >= 1) ? 1 : 0);
        iK3 = ((m_iSimplex[iC][2] >= 1) ? 1 : 0);
        iL3 = ((m_iSimplex[iC][3] >= 1) ? 1 : 0);

        float fX1 = (fX00 - iI1 + fG4);
        float fY1 = (fY00 - iJ1 + fG4);
        float fZ1 = (fZ00 - iK1 + fG4);
        float fW1 = (fW00 - iL1 + fG4);
        float fX2 = (fX00 - iI2 + (2.0 * fG4));
        float fY2 = (fY00 - iJ2 + (2.0 * fG4));
        float fZ2 = (fZ00 - iK2 + (2.0 * fG4));
        float fW2 = (fW00 - iL2 + (2.0 * fG4));
        float fX3 = (fX00 - iI2 + (3.0 * fG4));
        float fY3 = (fY00 - iJ2 + (3.0 * fG4));
        float fZ3 = (fZ00 - iK2 + (3.0 * fG4));
        float fW3 = (fW00 - iL2 + (3.0 * fG4));
        float fX4 = (fX00 - 1.0 + (4.0 * fG4));
        float fY4 = (fY00 - 1.0 + (4.0 * fG4));
        float fZ4 = (fZ00 - 1.0 + (4.0 * fG4));
        float fW4 = (fW00 - 1.0 + (4.0 * fG4));

        int iII     = (iI & 255);
        int iJJ     = (iJ & 255);
        int iKK     = (iK & 255);
        int iLL     = (iL & 255);
        int iGi0    = (m_iPerm[iII + m_iPerm[iJJ + m_iPerm[iKK + m_iPerm[iLL]]]] % 32);
        int iGi1    = (m_iPerm[(iII + iI1) + m_iPerm[(iJJ + iJ1) + m_iPerm[(iKK + iK1) + m_iPerm[iLL + iL1]]]] % 32);
        int iGi2    = (m_iPerm[(iII + iI2) + m_iPerm[(iJJ + iJ2) + m_iPerm[(iKK + iK2) + m_iPerm[iLL + iL2]]]] % 32);
        int iGi3    = (m_iPerm[(iII + iI3) + m_iPerm[(iJJ + iJ3) + m_iPerm[(iKK + iK3) + m_iPerm[iLL + iL3]]]] % 32);
        int iGi4    = (m_iPerm[(iII + 1) + m_iPerm[(iJJ + 1) + m_iPerm[(iKK + 1) + m_iPerm[iLL + 1]]]] % 32);

        float fT0 = (0.6 - (fX00 * fX00) - (fY00 * fY00) - (fZ00 * fZ00) - (fW00 * fW00));
        if (fT0 < 0) {
            fN0 = 0;
        } else {
            fT0 *= fT0;
            fN0  = ((fT0 * fT0) * dot(m_iGrad3[iGi0], fX00, fY00, fZ00, fW00));
        }

        float fT1 = (0.6 - (fX1 * fX1) - (fY1 * fY1) - (fZ1 * fZ1) - (fW1 * fW1));
        if (fT1 < 0) {
            fN1 = 0;
        } else {
            fT1 *= fT1;
            fN1  = ((fT1 * fT1) * dot(m_iGrad3[iGi1], fX1, fY1, fZ1, fW1));
        }

        float fT2 = (0.6 - (fX2 * fX2) - (fY2 * fY2) - (fZ2 * fZ2) - (fW2 * fW2));
        if (fT2 < 0) {
            fN2 = 0;
        } else {
            fT2 *= fT2;
            fN2  = ((fT2 * fT2) * dot(m_iGrad3[iGi2], fX2, fY2, fZ2, fW2));
        }

        float fT3 = (0.6 - (fX3 * fX3) - (fY3 * fY3) - (fZ3 * fZ3) - (fW3 * fW3));
        if (fT3 < 0) {
            fN3 = 0;
        } else {
            fT3 *= fT3;
            fN3  = ((fT3 * fT3) * dot(m_iGrad3[iGi3], fX3, fY3, fZ3, fW3));
        }

        float fT4 = (0.6 - (fX4 * fX4) - (fY4 * fY4) - (fZ4 * fZ4) - (fW4 * fW4));
        if (fT4 < 0) {
            fN4 = 0;
        } else {
            fT4 *= fT4;
            fN4  = ((fT4 * fT4) * dot(m_iGrad3[iGi4], fX4, fY4, fZ4, fW4));
        }

        return (27.0 * (fN0 + fN1 + fN2 + fN3 + fN4));
    }
};
