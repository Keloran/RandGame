#!/bin/bash

# Delete CMake Stuff
rm -rf `find . -type d -name CMakeFiles`
rm -rf `find . -type d -name build`
rm -rf `find . -type f -name CMakeCache.txt`
rm -rf `find . -type f -name Makefile`
rm -rf `find . -type f -name cmake_install.cmake`

# Delete old libraries
rm -rf `find . -type f -name libGame.a`
rm -rf `find . -type f -name libValkyrie.a`
rm -rf `find . -type f -name libValkyrieEngine.a`
rm -rf `find . -type f -name libThirdPartyLibs.a`
rm -rf `find . -type f -name libGameLibrary.a`
rm -rf `find . -type f -name libSQLite.a`
rm -rf `find . -type f -name libNames.a`
rm -rf `find . -type f -name libMarkov.a`
rm -rf `find . -type f -name libSimplex.a`
rm -rf `find . -type f -name libNordicOS.a`
rm -rf `find . -type f -name libAngelscript.a`

# Delete Binary
rm -rf `find . -type f -name RandGame.app`
rm -rf `find . -type f -name RandGame.log`
