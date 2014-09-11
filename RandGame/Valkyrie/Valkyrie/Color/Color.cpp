//
//  Color.cpp
//  Valkyrie
//
//  Created by Max Hooton on 11/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Color.hpp"

namespace NordicArts {
    namespace ValkyrieNS {
        const Color Color::Black(0, 0, 0);
        const Color Color::White(255, 255, 255);
        const Color Color::Red(255, 0, 0);
        const Color Color::Green(0, 255, 0);
        const Color Color::Blue(0, 0, 255);
        const Color Color::Yellow(255, 255, 0);
        const Color Color::Magenta(255, 0, 255);
        const Color Color::Cyan(0, 255, 255);
        const Color Color::Transparent(0, 0, 0, 0);
        
        Color::Color() : m_iRed(0), m_iGreen(0), m_iBlue(0), m_iAlpha(255) {
        }
        
        Color::Color(uint8_t iRed, uint8_t iGreen, uint8_t iBlue, uint8_t iAlpha) : m_iRed(iRed), m_iGreen(iGreen), m_iBlue(iBlue), m_iAlpha(iAlpha) {
        }
        
        // Operator Overrides
        bool operator ==(const Color &oLeft, const Color &oRight) {
            return (
                (oLeft.m_iRed == oRight.m_iRed) &&
                (oLeft.m_iGreen == oRight.m_iGreen) &&
                (oLeft.m_iBlue == oRight.m_iBlue) &&
                (oLeft.m_iAlpha == oRight.m_iAlpha)
            );
        }
        
        bool operator !=(const Color &oLeft, const Color &oRight) {
            return !(oLeft == oRight);
        }
        
        Color operator +(const Color &oLeft, const Color &oRight) {
            return Color(
                (uint8_t(std::min(int(oLeft.m_iRed) + oRight.m_iRed, 255))),
                (uint8_t(std::min(int(oLeft.m_iGreen) + oRight.m_iGreen, 255))),
                (uint8_t(std::min(int(oLeft.m_iBlue) + oRight.m_iBlue, 255))),
                (uint8_t(std::min(int(oLeft.m_iAlpha) + oRight.m_iAlpha, 255)))
            );
        }
        
        Color operator -(const Color &oLeft, const Color &oRight) {
            return Color(
                (uint8_t(std::min(int(oLeft.m_iRed) - oRight.m_iRed, 255))),
                (uint8_t(std::min(int(oLeft.m_iGreen) - oRight.m_iGreen, 255))),
                (uint8_t(std::min(int(oLeft.m_iBlue) - oRight.m_iBlue, 255))),
                (uint8_t(std::min(int(oLeft.m_iAlpha) - oRight.m_iAlpha, 255)))
            );
        }
        
        Color operator *(const Color &oLeft, const Color &oRight) {
            return Color(
                (uint8_t(std::min(int(oLeft.m_iRed) * oRight.m_iRed, 255))),
                (uint8_t(std::min(int(oLeft.m_iGreen) * oRight.m_iGreen, 255))),
                (uint8_t(std::min(int(oLeft.m_iBlue) * oRight.m_iBlue, 255))),
                (uint8_t(std::min(int(oLeft.m_iAlpha) * oRight.m_iAlpha, 255)))
            );
        }
        
        Color &operator +=(Color &oLeft, const Color &oRight) {
            return oLeft = (oLeft + oRight);
        }
        
        Color &operator -=(Color &oLeft, const Color oRight) {
            return oLeft = (oLeft - oRight);
        }
        
        Color &operator *=(Color &oLeft, const Color oRight) {
            return oLeft = (oLeft * oRight);
        }
    };
};