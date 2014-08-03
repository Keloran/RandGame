#!/bin/bash
oldCC=$CC
oldCXX=$CXX

# Set the compiler to clang
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

# Run the cleaner and then build to make sure its fresh
clear
sh cleaner.sh
cmake .
make

# Set Compiler Back
export CC=$CC
export CXX=$CXX

# Cleanup the mess
rm -rf `find . -type d -name CMakeFiles`
rm -rf `find . -type d -name build`
rm -rf `find . -type f -name CMakeCache.txt`
rm -rf `find . -type f -name Makefile`
rm -rf `find . -type f -name cmake_install.cmake`

# Run the app to make sure its stable
./RandGame.app
