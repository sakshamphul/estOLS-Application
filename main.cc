#include <iostream>
#include <fstream>
#include <chrono>
#include "main.hh"

extern "C" {
#include <gsl/gsl_matrix_float.h>
#include <gsl/gsl_linalg.h>

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //!
    //! @brief This file contains the main function that control the flow of this application
    //! @author Saksham Phul
    //! @contact phulsaksham2@gmail.com
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int arg, char *argc[])
{
     auto begin = std::chrono::high_resolution_clock::now();
     size_t n;
     size_t m;
     char* str_X;
     char* str_Y;
     char* str_OUT;
     std::cout<<" Version 1.0.0 estOlS application \n Git repo: https://github.com/sakshamphul/estOLS-Application \n" ;
     if(arg<11){       
		   if(arg==1)
			  help_function(0);
		   else if (strcmp(argc[1],"-help")==0) 
			  help_function(1);		   
		   else{
			  std::cout<<" Provide all the required flags or use -help flag to call for more information "<<std::endl;
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
     
   //  read_matrix_from_file(X,str_X);
     
   
    if(strcmp(str_X,"random")==0){
			  fill_random_matrix(X,n,m);   
			  std::cout<<" X gets random float values \n";
    }
    else{
	if(!read_matrix_from_file(X,str_X,X->size1,X->size2)){ return 0;}
			  std::cout<<" X gets values from file "<<str_X<<"\n";
    }	
    
    if (strcmp(str_Y,"random")==0){
			  fill_random_matrix(Y,n,1);
			  std::cout<<" Y gets random float values \n";
    }
    else{
	if(!read_matrix_from_file(Y,str_Y,Y->size1,Y->size2)){ return 0;}
			  std::cout<<" Y gets values from file "<<str_Y<<"\n";
	}
//print_matrix_in_file(Y,str_OUT);

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
    
    //auto stop_B = std::chrono::high_resolution_clock::now();
    //duration =std::chrono::duration_cast<std::chrono::seconds>(stop_B-stop_in);
    //std::cout<<" Computation of X(T)*Y completed in time "<<duration.count()<<" seconds"<<std::endl;

    gsl_matrix_free(X);
    gsl_matrix_free(Y);
   
    gsl_matrix *C = gsl_matrix_alloc(m, 1);
    //multiply    C= A * B
    gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,1.0,inverse,B,0.0,C);
    gsl_matrix_free(inverse);
    gsl_matrix_free(B);
    
    auto stop = std::chrono::high_resolution_clock::now();
    duration =std::chrono::duration_cast<std::chrono::seconds>(stop-start);
    std::cout<<" Time spent in computation: "<<duration.count()<<" seconds"<<std::endl;
    
     if(strcmp(str_OUT,"display")==0)
		print_matrix(C);
	else	
		print_matrix_in_file(C,str_OUT);
    gsl_matrix_free(C);
    
    duration =std::chrono::duration_cast<std::chrono::seconds>(stop-begin);
    std::cout<<" Run time estOLS Application: "<<duration.count()<<" seconds"<<std::endl;
  
    return 0;
}
