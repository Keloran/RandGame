#ifndef NORDICARTS_OS_LOAD_H
#define NORDICARTS_OS_LOAD_H

// Includes
#include <cassert> // Asserts
#include <time.h> // Time
#include <ctime> // Time
#include <iostream> // Input-Output stream
#include <string> // Strings
#include <string.h> // Strings
#include <stdexcept> // Excepetions
#include <cmath> // Maths
#include <fstream> // Streams
#include <sstream> // Streams
#include <vector> // Vector Array
#include <cstddef> // Standard Defs
#include <stdlib.h> // STD lib
#include <stdio.h> // STD input-Output
#include <cstring> // Strings
#include <list> // List Array
#include <stdarg.h> // STD Arguments
#include <stdint.h> // STD integer
#include <array> // Array
#include <iomanip> // Input-Output Manipulation
#include <math.h> // Math
#include <algorithm> // Misc
#include <unordered_map> // Unordered Map
#include <map> // Map

// OSX Includes
#ifdef __OBJC__
    #import <Cocoa/Cocoa.h>
    #import <Foundation/Foundation.h>
    #import <CoreFoundation/CoreFoundation.h>
#endif

// Is it Windows
#if defined(__APPLE__) || defined(__APPLE_CC__)
    #define nonWindows true
#endif

#if defined(__LINUX__) || defined(__linux__) || defined(linux)
    #define nonWindows true
#endif

#endif
