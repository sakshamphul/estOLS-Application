#include <iostream>
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <stdlib.h>
#include "main.hh"
#include <thread>
extern "C" {
#include "gsl/gsl_matrix_float.h"
#include <gsl/gsl_linalg.h>

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //!
    //! @brief This file contains the main function that control the flow of this application
    //! @author Saksham Phul
    //!
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void help_function(const int carry)
{
  	std::cout<<"-help: will provide essential details to run this application \n";
	if(carry==1){
	  	std::cout<<"Flags that will help run this application are as follows:\n";
		std::cout<<"-x: takes a filename name as a input and set up the X matrice. You can also use random keyword to fill these matrices with random values For example: -x random or -x filename. \n";
    		std::cout<<"-y: takes a filename name as a input and set up the Y matrice. You can also use random keyword to fill these matrices with random values For example: -x random or -x filename. \n";
    		std::cout<<"-size_n: provide the number of rows for matrix X and Y \n";
    		std::cout<<"-size_m: provide the number of columns for matrix X \n";
                std::cout<<"-o: provide the name of file to store the output. You can also use display keyword to print final output on the screen. For example -o display \n";
                std::cout<<"Command line format: ./estOLS -x X_file -y Y_file -size_n 10000 -size_m 500 -o result \n";
	}
}

int main(int arg, char *argc[])
{
     
     size_t n;
     size_t m;
     char* str_X;
     char* str_Y;
     char* str_OUT;
     std::cout<<"Version 1.0.0 estOlS application\n @copyright: Saksham Phul \n Git repo: https://github.com/sakshamphul/estOLS-Application \n" ;
     if(arg<11){       
		   if(arg==1)
		     help_function(0);
		   else if (strcmp(argc[1],"-help")==0) 
			help_function(1);		   
		   else{
		   std::cout<<"Provide all the required flags or use -help flag to call for more information "<<std::endl;
		   }
		   return 0;		   
	    }
     for(int i(0);i<arg;++i)
	{
		    if(strcmp(argc[i],"-size_n")==0){
			  n=atoi(argc[i+1]);
		    }
		    else if(strcmp(argc[i],"-size_m")==0){
			  m=atoi(argc[i+1]);
		    }
		    else if(strcmp(argc[i],"-x")==0){
				str_X=argc[i+1];
			  }
		    else if(strcmp(argc[i],"-y")==0){
					str_Y=argc[i+1];
			}
		    else if(strcmp(argc[i],"-o")==0){
                                        str_OUT=argc[i+1];
			 }	  
	}
    
     gsl_matrix *X = gsl_matrix_alloc(n, m);
     gsl_matrix *Y = gsl_matrix_alloc(n, 1);
   
    if(strcmp(str_X,"random")==0){
		  std::cout<<"X gets random float values \n";
	    fill_random_matrix(X,n,m);   
    }
    else{
	std::cout<<"Reading X from file "<<str_X<<"\n";
	if(!read_file(X,str_X)){ return 0;}
    }	
    
    if (strcmp(str_Y,"random")==0){
		  std::cout<<"Y gets random float values \n";
	    fill_random_matrix(Y,n,1);
    }
    else{
          std::cout<<"Reading Y from file "<<str_Y<<"\n";
	if(!read_file(Y,str_Y)){ return 0;}
    }

    auto start = std::chrono::high_resolution_clock::now();
    gsl_matrix *A = gsl_matrix_alloc(m, m);
    //multiply    A= Xtranspose * X
    gsl_blas_dgemm(CblasTrans,CblasNoTrans,1.0,X,X,0.0,A);
    auto start_in = std::chrono::high_resolution_clock::now();

    auto duration =std::chrono::duration_cast<std::chrono::seconds>(start_in-start);
    std::cout<<" Computation of X(T)*X completed in time "<<duration.count()<<" seconds"<<std::endl;
    gsl_matrix *inverse = invert_a_matrix(A,m);
    gsl_matrix_free(A);
    auto stop_in = std::chrono::high_resolution_clock::now();
    duration =std::chrono::duration_cast<std::chrono::seconds>(stop_in-start_in);
    std::cout<<" Inverse of X(T)*X completed in time "<<duration.count()<<" seconds"<<std::endl;

    gsl_matrix *B = gsl_matrix_alloc(m, 1);
    //multiply    B= Xtranspose * Y
    gsl_blas_dgemm(CblasTrans,CblasNoTrans,1.0,X,Y,0.0,B);
    
    auto stop_B = std::chrono::high_resolution_clock::now();

    duration =std::chrono::duration_cast<std::chrono::seconds>(stop_B-stop_in);
    std::cout<<" Computation of X(T)*Y completed in time "<<duration.count()<<" seconds"<<std::endl;

    gsl_matrix_free(X);
    gsl_matrix_free(Y);
   
    gsl_matrix *C = gsl_matrix_alloc(m, 1);
    //multiply    C= A * B
    gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,1.0,inverse,B,0.0,C);

    gsl_matrix_free(inverse);
    gsl_matrix_free(B);
    auto stop = std::chrono::high_resolution_clock::now();
    duration =std::chrono::duration_cast<std::chrono::seconds>(stop-stop_B);
    std::cout<<" Computation of inverse(XT*X)*Y completed in time "<<duration.count()<<" seconds"<<std::endl;
    duration =std::chrono::duration_cast<std::chrono::seconds>(stop-start);
    std::cout<<" Total time is "<<duration.count()<<" seconds"<<std::endl;
    
	if(strcmp(str_OUT,"display")==0)
	   print_matrix(C);
	else	
	   print_matrix_in_file(C,str_OUT);
    gsl_matrix_free(C);
    return 0;
}
