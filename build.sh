#!/bin/bash

g++ -std=c++11 -O3 -c -I /home/saksham/Desktop/test/gsl-2.7.1/gsl-bin/include/  main.cc

g++ -std=c++11 -L/home/saksham/Desktop/test/gsl-2.7.1/gsl-bin/lib/ main.o -lgsl -lgslcblas -lm -o estOLS




