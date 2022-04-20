# estOLS-Application: A C/C++ based command line application to compute ordinary least square)
This application calculates the ordinary least squares estimates from matrix vector operations using GNU scientific library. The equation is as follows:

**GNU scientific Library:** https://www.gnu.org/

Version 1.0.0

## Installation

Get the the current stable version GSL 2.7: Download GSL - GNU scientific Library :- https://www.gnu.org/software/gsl/

Find the compressed file in .gz format and extract it in the folder where you want to install GNU scientific library:

     tar -xf gsl-latest.tar.gz

cd into gsl-2.*.* folder to install and create binaries to run our application

     cd gsl-2.*.*/

Configure the GNU library for our workstation before installation:

    ./configure --prefix={absolute_path_to_installation_folder}

Now, compile the library to generate binaries:

     make 

Installation will write files to {absolute_path_to_installation_folder}. Therefore, write permissions are required to run following command: 

    make install

GNU installation is complete

Create a folder and clone estOLS respo: 

    git clone https://github.com/sakshamphul/estOLS-Application

Compile main.cc file with a path to GNU library include folder to find the header files used in main.cc

    g++ -std=c++11 -c -O3 -I {absolute_path_to_installation_folder}/include/  main.cc

Link our library with GNU libraries using following command:

    g++ -std=c++11 -L{absolute_path_to_installation_folder}/lib/ main.o -lgsl -lgslcblas -lm

linking application with shared library requires path by application excutable during runtime. Therefore, before we run our application we must provide our workstation with new LD_Library_Path to look for runtime libraries(shared libraries). You can either set up LD_LIBRARY_PATH in your bash profile or simply set up variable for current terminal session: 

To setup LD_LIBRARY_Path for current terminal session:
 
    export LD_LIBRARY_Path=/ssd1/c++_bootcamp/assignment/gsl-2.7.1/gsl-install/lib/

To add this session to your profile, navigate and open .bashrc file This is optional 
    
    sudo vi /etc/.bashrc

You would require root access to update .bashrc file.
Add following line at the end of the .bashrc file
 
    export LD_LIBRARY_Path=/ssd1/c++_bootcamp/assignment/gsl-2.7.1/gsl-install/lib/
    
run bashrc file to update your changes
    source /etc/.bashrc
    
**estOLS: A C++ based command line application**

It's a pre compiled application. Hence, all you need is estOLS executable to run it.

To call for help use -help flag

     estOLS -help
     
To run OLS computation

     estOLS -x FILENAME_X_MATRIX -Y FILENAME_Y_MATRIX -size_n INT -size_m INT -o display

To run OLS computation with randomly set values for matrix X and Y, replace FILENAME with "random" keyword:

     estOLS -x random -Y random -size_n INT -size_m INT -o output_filename
    
Output matrix is stored in the file given in -o flag. You can also print the output on the terminal by using display keyword.
