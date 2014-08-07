#include "./OSX.hpp"

namespace NordicArts {
    std::string OSSpecific::ResourcePath(std::string cFileName) {
        NSString *pFileName = [NSString stringWithCString: cFileName.c_str() encoding:NSUTF8StringEncoding];
        NSString *pPath     = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent: pFileName];

        return std::string([pPath cStringUsingEncoding: NSUTF8StringEncoding]);
    };
};
