#!/bin/bash
sh cleaner.sh
cmake .
make
./RandGame.app
