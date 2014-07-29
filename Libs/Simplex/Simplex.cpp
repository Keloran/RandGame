#include "./Simplex.h"

namespace NordicArts {
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
        return 0.0f;
    }

    float Simplex::rawNoise4d(float fX, float fY, float fZ, float fW) {
        return 0.0f;
    }
};
