#!/bin/bash
# Compile and run c++ program

#rm $1 &&
gcc $1.cpp -lm -lstdc++ -o $1 && ./$1
#gcc $1.cpp -o $1 && ./$1
