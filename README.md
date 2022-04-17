# Ordinary least square (estOLS-Application)
This application calculates the ordinary least squares estimates from matrix vector operations using GNU scientific library. The equation is as follows:

**Download GSL - GNU scientific Library:** https://www.gnu.org/software/gsl/

Version 0.9.4.

## Installation

Get the the current stable version GSL 2.7: Download GSL - GNU scientific Library :- https://www.gnu.org/software/gsl/

Find the compressed file in .gz format and extract it in the folder where you want to install GNU scientific library:

     tar -xf gsl-latest.tar.gz

cd into gsl-2.*.* folder to install and create binaries to run our application

     cd gsl-2.*.*/

make required

Let's configure the GNU library for your workstation before installation:

    ./configure --prefix={absolute_path_to_installation_folder}

Now,Let's compile the library to generate binaries:

     make 

Installation will write files to {absolute_path_to_installation_folder}. Therefore,write permissions are required. 

    make install

GNU installation is complete

Let's create a folder and clone estOLS respo: 

    git clone https://github.com/sakshamphul/estOLS-Application

Let's compile main.cc file with a path to GNU library to find the header files

    g++ -std=c++11 -c -pthread -O3 -I {absolute_path_to_installation_folder}/include/  main.cc

Let's link our library with GNU using following command:

    g++ -std=c++11 -pthread -L{absolute_path_to_installation_folder}/lib/ main.o -lgsl -lgslcblas -lm

linking with shared library requires path to excutalble to run,therefore, 
Before we run our application we must provide workstation with new LD_Library_Path to look for runtime libraries. You can either set up LD_LIBRARY_PATH in your bash profile or just set up variable for current terminal session:
 To setup LD_LIBRARY_Path for 
export LD_LIBRARY_Path=/ssd1/c++_bootcamp/assignment/gsl-2.7.1/gsl-install/lib/

echo $LD_LIBRARY_Path
 remind user to drop the path directly into profile file
