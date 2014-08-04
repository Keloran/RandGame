#ifndef NORDICARTS_INCLUDES_H
#define NORDICARTS_INCLUDES_H

// General System Includes
#include <iostream>
#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <cstdint>
#include <chrono>

// ThirdParty Includes
#include "./ThirdParty/General/sqlite/sqlite3.h"
#include "./ThirdParty/General/sqlite/sqlite3ext.h"

// System Specific Includes
#if defined(__APPLE__) || defined (__OSX__)
	#include "./Includes/OSX.hpp"
#elif defined (__LINUX__) || defined(__POSIX__)
	#include "./Includes/Linux.hpp"
#elif defined(__WINDOWS__) || defined(__WIN32__)
	#include "./Includes/Windows.hpp"
#endif

#endif
