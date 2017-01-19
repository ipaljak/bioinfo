#!/bin/bash

set -o xtrace

echo " *** Downloading data"
wget https://www.dropbox.com/s/a40dhhfchojyf0c/consenus_input.zip?dl=0

unzip consenus_input.zip?dl=0

mv *fast* data

echo " *** Installing graphmap"
git clone https://github.com/isovic/graphmap.git
cd graphmap
make modules
make

echo " *** Compiling source code"
g++ src/Reading.cpp -o src/reading

g++ -std=c++11 src/sparc.cpp -o src/sparc

echo " *** Done."

