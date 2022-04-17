#include <iostream>
#include <fstream>
#include <stdio.h>
#include <chrono>
#include <stdlib.h>
#include "invert.hh"
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

void help_function()
{
  std::cout<<"Flags that help run this application are as follows:\n";
  std::cout<<"-help - will provide essential important to run this application. \n";
  std::cout<<"-x: takes a filename name as a input and set up the X matrice. You can also use random keyword to fill these matrices with random values For example: -x random or -x filename. \n";
    std::cout<<"-y: takes a filename name as a input and set up the Y matrice. You can also use random keyword to fill these matrices with random values For example: -x random or -x filename. \n";
    std::cout<<" -size_n: provide the number of rows for matrix X and Y \n";
    std::cout<<" -size_m: provide the number of columns for matrix X \n";
}


int main(int arg, char *argc[])
{
     
     size_t n;
     size_t m;
     char* str_X;
     char* str_Y;
     if(arg<9){
       
		   if(arg==1 || strcmp(argc[1],"-help")==0){
		     help_function();
		    }
		   else{
		   std::cout<<"Provide all the required flags or use -help flag to call for more information "<<std::endl;
		   }
		   return 0;		   
	    }
         
     for(int i(0);i<arg;++i)
	{ //std::cout<<arg<<" "<<argc[i]<<std::endl;
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
	}
    
     gsl_matrix *X = gsl_matrix_alloc(n, m);
     gsl_matrix *Y = gsl_matrix_alloc(n, 1);
    
//     if( (!str_X && !str_Y) ){
//				  if(strcmp(str_X,"random")!=0 && strcmp(str_Y,"random")!=0){
//						 std::cout<<"Provide data for matrics computation using -x and -m flags"<<std::endl;
//		     std::cout<<"You can either provide name with -x , -y flags or choose random mode to generate the data randomly"<<std::endl;
//		    return 0;
//				  }
      
						
    if(strcmp(str_X,"random")==0){
//		  printf("X is random \n");
	    fill_random_matrix(X,n,m);   
    }
    else{
	if(!read_file(X,str_X)){ return 0;}
    }	
    
    if (strcmp(str_Y,"random")==0){
//		  printf("Y is random \n");
	    fill_random_matrix(Y,n,1);
    }
    else{
	if(!read_file(Y,str_Y)){ return 0;}
    }	
 //    printf("Original matrix:\n");
//    printf("X is \n");
//    std::thread th(print_matrix,X,n,m);
 //   print_matrix(X,n,m);
//    printf("Y is \n");
 //   print_matrix(Y,n,1);
    write_file(X); 
    
    auto start = std::chrono::high_resolution_clock::now();
    gsl_matrix *A = gsl_matrix_alloc(m, m);
    //multiply    A= Xtranspose * X
    gsl_blas_dgemm(CblasTrans,CblasNoTrans,1.0,X,X,0.0,A);
    
    auto start_in = std::chrono::high_resolution_clock::now();
     
    gsl_matrix *inverse = invert_a_matrix(A,m);
    gsl_matrix_free(A);
    
    auto stop_in = std::chrono::high_resolution_clock::now();
    gsl_matrix *B = gsl_matrix_alloc(m, 1);
    //multiply    B= Xtranspose * Y
    gsl_blas_dgemm(CblasTrans,CblasNoTrans,1.0,X,Y,0.0,B);
    
    auto stop_B = std::chrono::high_resolution_clock::now();
    
    gsl_matrix_free(X);
    gsl_matrix_free(Y);
    
    //print_matrix(B,m,1);
    gsl_matrix *C = gsl_matrix_alloc(m, 1);
    //multiply    C= A * B
    gsl_blas_dgemm(CblasNoTrans,CblasNoTrans,1.0,inverse,B,0.0,C);
//    th.join();
    gsl_matrix_free(inverse);
    gsl_matrix_free(B);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =std::chrono::duration_cast<std::chrono::seconds>(stop-start);
    auto duration_in =std::chrono::duration_cast<std::chrono::seconds>(stop_in-start_in);
    auto duration_B =std::chrono::duration_cast<std::chrono::seconds>(stop_in-stop_B);
    auto duration_first =std::chrono::duration_cast<std::chrono::seconds>(start_in-start);
    
    std::cout<<"Total time is "<<duration.count()<<" seconds"<<std::endl;
    std::cout<<"Inverse time is "<<duration_in.count()<<" seconds"<<std::endl;
    std::cout<<"A comp time is "<<duration_first.count()<<" seconds"<<std::endl;
    std::cout<<"B comp time is "<<duration_B.count()<<" seconds"<<std::endl;
    
    write_file(C);
    gsl_matrix_free(C);
    return 0;
}
