#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <gsl/gsl_matrix_float.h>
#include <gsl/gsl_linalg.h>

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //!
    //! @brief This is a header file that contains supporting functions for main.cc 
    //! @author Saksham Phul
    //!
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
void write_file(gsl_matrix *C){
	    FILE *in_file;
	   
	    in_file=fopen("output","w+");
	    if(in_file!=NULL){
		//	  fputs("Final matrix: \n",in_file);		  
			  gsl_matrix_fprintf(in_file,C,"%f");
	    }
	    fclose(in_file);
   
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

void
print_matrix(gsl_matrix *matrix,size_t n,size_t m)
{
    size_t i, j;
    float element;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            element = gsl_matrix_get(matrix, i, j);
            printf("%f ", element);
        }
        printf("\n");
    }
}

void
fill_random_matrix(gsl_matrix *matrix,size_t n,size_t m)
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
gsl_matrix *
invert_a_matrix(gsl_matrix *matrix,size_t size)
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