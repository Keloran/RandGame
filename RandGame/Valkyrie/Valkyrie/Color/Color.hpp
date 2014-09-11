//
//  Color.h
//  Valkyrie
//
//  Created by Max Hooton on 11/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_Valkyrie_Color_H
#define NordicArts_Valkyrie_Color_H

#include "../Includes.hpp"
#include <NordicOS/OS.hpp>

namespace NordicArts {
    namespace ValkyrieNS {
        class Color {
        // Variables
        public:
            static const Color Black;
            static const Color White;
            static const Color Red;
            static const Color Green;
            static const Color Blue;
            static const Color Yellow;
            static const Color Magenta;
            static const Color Cyan;
            static const Color Transparent;
            
            uint8_t m_iRed;
            uint8_t m_iGreen;
            uint8_t m_iBlue;
            uint8_t m_iAlpha;
            
        protected:
        private:
            
        // Methods
        public:
            Color();
            Color(uint8_t iRed, uint8_t iGreen, uint8_t iBlue, uint8_t iAlpha = 255);
        protected:
        private:
            
        };
        
        // Operator Overrides
        bool operator ==(const Color &oLeft, const Color &oRight);
        bool operator !=(const Color &oLeft, const Color &oRight);
        
        Color operator +(const Color &oLeft, const Color &oRight);
        Color operator -(const Color &oLeft, const Color &oRight);
        Color operator *(const Color &oLeft, const Color &oRight);
        
        Color &operator +=(const Color &oLeft, const Color &oRight);
        Color &operator -=(const Color &oLeft, const Color &oRight);
        Color &operator *=(const Color &oLeft, const Color &oRight);
    };
};

#endif /* defined(__Valkyrie__Color__) */
