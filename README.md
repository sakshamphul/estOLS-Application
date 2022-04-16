# estOLS-Application
Download GSL - GNU scientific Library :- https://www.gnu.org/software/gsl/
you can download the current stable version GSL 2.7 relaesed on 1 June 2021

Previous link provides a compressed file in .gs format

Extract this file in a target folder using 

tar -xf gsl-latest.tar.gz

Let's visit inside this folder to install and create binaries to run our application

cd gsl-2.*.*/

make required
steps to install GNU in your workstation:

1)  ./configure --prefix=path to install gsl-bin


Now,Let's compile the library to generate binaries
2) make 
Note this may time sometime to complie based on the number of cores avaialble in your workstation.

3) make install

Installtion is complete adn we can use the library now.

Let's create a folder where we will clone this resppgigary 

git clone 

Let's compile out main.cc file with a path to GNU library to find th eheader files
g++ -std=c++11 -c -I /ssd1/c++_bootcamp/assignment/gsl-2.7.1/gsl-install/include/  main.cc

Let's link our library with GNU using following command:
g++ -std=c++11 -L/ssd1/c++_bootcamp/assignment/gsl-2.7.1/gsl-install/lib/ main.o -lgsl -lgslcblas -lm

linking with shared library requires path to excutalble to run,therefore, 
Before we run our application we should provide system another LD_Library_Path

export LD_LIBRARY_Path=/ssd1/c++_bootcamp/assignment/gsl-2.7.1/gsl-install/lib/

echo $LD_LIBRARY_Path
 remind user to drop the path directly into profile file
