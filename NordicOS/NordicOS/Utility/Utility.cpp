#include "./Utility.hpp"
#include "../ExceptionHandler/ExceptionHandler.hpp"

namespace NordicArts {
    namespace NordicOS {
        Utility::Utility() {
        }

        void Utility::isPlatformCompatible() {
            struct sizeTest {
                std::string cInfo;

                size_t tSize;
                size_t tExpectedSize;

                sizeTest(const std::string &cInfoIn, size_t tSizeIn, size_t tExpectSizeIn) : cInfo(cInfoIn), tSize(tSizeIn), tExpectedSize(tExpectedSizeIn) {}
            };

            // Tests
            std::vector<sizeTest> vTests;
            vTests.push_back(sizeTest("sizeof(char)", sizeof(char), 1));
            vTests
        }
    };
};
