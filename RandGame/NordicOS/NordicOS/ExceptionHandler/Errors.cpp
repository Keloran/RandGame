//
//  Errors.cpp
//  NordicOS
//
//  Created by Max Hooton on 12/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./Errors.hpp"
#include <streambuf>
#include <cstdio>

namespace {
    class DefaultErrStreamBuf : public std::streambuf {
    // Variables
    public:
    protected:
    private:
        
    // Methods
    public:
        DefaultErrStreamBuf() {
            static const int iSize = 64;
            char *pBuffer = new char[iSize];
            setp(pBuffer, (pBuffer + iSize));
        }
        
        ~DefaultErrStreamBuf() {
            sync();
            
            delete[] pbase();
        }
        
    protected:
    private:
        virtual int overflow(int iCharacter) {
            if ((iCharacter != EOF) && (pptr() != epptr())) {
                return sputc(static_cast<char>(iCharacter));
            } else if (iCharacter != EOF) {
                sync();
                
                return overflow(iCharacter);
            } else {
                return sync();
            }
        }
        
        virtual int sync() {
            if (pbase() != pptr()) {
                std::size_t nSize = static_cast<int>(pptr() - pbase());
                fwrite(pbase(), 1, nSize, stderr);
                
                setp(pbase(), epptr());
            }
            
            return 0;
        }
    };
};

namespace NordicArts {
    namespace NordicOS {
        std::ostream &error() {
            static DefaultErrStreamBuf oBuffer;
            static std::ostream stream(&oBuffer);
            
            return stream;
        }
        
        std::ostream &Errors() {
            return error();
        }
    };
};
