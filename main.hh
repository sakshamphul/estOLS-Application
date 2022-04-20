#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //!
    //! @brief This is a header file that contains supporting functions for main.cc 
    //! @author Saksham Phul
    //! @copyright Saksham Phul
    //!
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

bool read_file(gsl_matrix *C,char str[]){
	    FILE *in_file=fopen(str,"r");
	    if(in_file!=NULL){
			  gsl_matrix_fscanf(in_file,C);
			  fclose(in_file);
			  return true;
	    }
	    else
	    {
		std::cout<<"Input files not found! "<<"\n";
		return false;
	    }
}

void print_matrix(gsl_matrix *matrix)
{
	    size_t i=matrix->size1; 
	    size_t j=matrix->size2;
	    float element;

	    for (unsigned int ii = 0; ii < i; ++ii) {
			  for (unsigned int jj = 0; jj < j; ++jj) {
					element = gsl_matrix_get(matrix, ii, jj);
					printf("%f ", element);
			  }
	    printf("\n");
	    }
}

void print_matrix_in_file(gsl_matrix *matrix,char filename[])
{
	    std::ofstream file;
	    file.open(filename);
    
	    size_t i=matrix->size1; 
	    size_t j=matrix->size2;
	    float element;

	    std::cout<<"Writing matrix to "<<filename<<std::endl;
	    for (unsigned int ii = 0; ii < i; ++ii) {
			  for (unsigned int jj = 0; jj < j; ++jj) {
					element = gsl_matrix_get(matrix, ii, jj);
					file<<element;
					file<<"\t";
			  }
		file<<"\n";
	    }
 file.close();
}

bool read_matrix_from_file(gsl_matrix *matrix,char filename[],size_t n,size_t m)
{
	    std::ifstream file(filename);
	    float element;
	    if(!file.fail()){
			  std::cout<<"Reading matrix from "<<filename<<std::endl;
			  for (unsigned int ii = 0; ii < n; ++ii) {
					for (unsigned int jj = 0; jj < m; ++jj) {
						    //element = gsl_matrix_get(matrix, ii, jj);
						    file>>element;
						    //std::cout<<element;
						    gsl_matrix_set(matrix, ii, jj,element);
					}
        //file<<"\n";
			  }
			  return true;
	    }
	    else
	    {
			  std::cout<<"Input file "<<filename<<" not found! "<<"\n";
			  return false;
	    }
	    file.close();
}


void fill_random_matrix(gsl_matrix *matrix,size_t n,size_t m)
{
	    size_t i, j;
	    float random;
	    float range = 1.0 * RAND_MAX;
	    for (i = 0; i < n; ++i) {
			  for (j = 0; j < m; ++j) {
					random = rand() / range;
					gsl_matrix_set(matrix, i, j, random);

			  }
	    }
}	
gsl_matrix *invert_a_matrix(gsl_matrix *matrix,size_t size)
{
	    gsl_permutation *p = gsl_permutation_alloc(size);
	    int s;
    // compute the LU decomposition
	    gsl_linalg_LU_decomp(matrix, p, &s);
    // compute the  inverse of the LU decomposition
	    gsl_matrix *inverse = gsl_matrix_alloc(size, size);
    // compute the LU inverse
	    gsl_linalg_LU_invert(matrix, p, inverse);
	    gsl_permutation_free(p);
	    return inverse;
}
/*    
void write_file(gsl_matrix *C){
	    FILE *in_file;
	   
	    in_file=fopen("RESULT","w+");
	    if(in_file!=NULL){
		//	  fputs("Final matrix: \n",in_file);		  
			  gsl_matrix_fprintf(in_file,C,"%f");
	    }
	    std::cout<<"final result written in the RESULT file \n";	
   
}
*/