#gcc -Wall -c -I /ssd1/c++_bootcamp/assignment/gsl-2.7.1/gsl-install/include/ invert.c 

g++ -std=c++11 -c -O3 -I /ssd1/c++_bootcamp/assignment/gsl-2.7.1/gsl-install/include/  main.cc
g++ -std=c++11 -L/ssd1/c++_bootcamp/assignment/gsl-2.7.1/gsl-install/lib/ main.o -lgsl -lgslcblas -lm -o estOLS

#gcc -L/ssd1/c++_bootcamp/assignment/gsl-2.7.1/gsl-install/lib/ invert.o -lgsl -lgslcblas -lm



