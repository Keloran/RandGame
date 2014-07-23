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

# Delete Binary
rm -rf `find . -type f -name RandGame.app`
