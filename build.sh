#!/bin/bash
oldCC=$CC
oldCXX=$CXX

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

sh cleaner.sh
cmake .
make

export CC=$CC
export CXX=$CXX

./RandGame.app
