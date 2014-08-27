//
//  FileUtils.cpp
//  NordicOS
//
//  Created by Max Hooton on 25/08/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#include "./FileUtils.hpp"

namespace NordicArts {
    namespace NordicOS {
        bool fileExists(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > cFileName) {
            std::cout << cFileName.c_str() << std::endl;
            false;
        }

        bool fileExists(std::string cFileName) {
            return fileExists(cFileName.c_str());
        }
        
        bool fileExists(const char *cFileName) {
            bool bExists = false;
            
            std::ifstream pFile(cFileName);
            if (pFile) {
                bExists = true;
                pFile.close();
            }
            
            return bExists;
        }
    };
};
