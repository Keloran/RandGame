//
//  NonCopyable.hpp
//  NordicOS
//
//  Created by Max Hooton on 13/09/2014.
//  Copyright (c) 2014 NordicArts.net. All rights reserved.
//

#ifndef NordicArts_NordicOS_NonCopyable_H
#define NordicArts_NordicOS_NonCopyable_H

namespace NordicArts {
    namespace NordicOS {
        class NonCopyable {
        // Variables
        public:
        protected:
        private:
            
        // Methods
        public:
        protected:
            NonCopyable() {}
            
        private:
            NonCopyable(const NonCopyable&);
            NonCopyable &operator =(const NonCopyable&);
            
        };
    };
};

#endif
