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

                sizeTest(const std::string &cInfoIn, size_t tSizeIn, size_t tExpectedSizeIn) : cInfo(cInfoIn), tSize(tSizeIn), tExpectedSize(tExpectedSizeIn) {}
            };

            // Tests
            std::vector<sizeTest> vTests;
            vTests.push_back(sizeTest("sizeof(char)", sizeof(char), 1));
            vTests.push_back(sizeTest("sizeof(unsigned char)", sizeof(unsigned char), 1));
            vTests.push_back(sizeTest("sizeof(short)", sizeof(short), 2));
            vTests.push_back(sizeTest("sizeof(unsigned short)", sizeof(unsigned short), 2));
            vTests.push_back(sizeTest("sizeof(int)", sizeof(int), 4));
            vTests.push_back(sizeTest("sizeof(unsigned int)", sizeof(unsigned int), 4));
            vTests.push_back(sizeTest("sizeof(long)", sizeof(long), 8));
            vTests.push_back(sizeTest("sizeof(unsigned long)", sizeof(unsigned long), 8));
            vTests.push_back(sizeTest("sizeof(unsigned )", sizeof(unsigned ), 4));
            vTests.push_back(sizeTest("sizeof(float)", sizeof(float), 4));
            vTests.push_back(sizeTest("sizeof(long long)", sizeof(long long), 8));
            vTests.push_back(sizeTest("sizeof(unsigned long long)", sizeof(unsigned long long), 8));
            vTests.push_back(sizeTest("sizeof(double)", sizeof(double), 8));
            vTests.push_back(sizeTest("sizeof(long double)", sizeof(long double), 16));
        }
    };
};
