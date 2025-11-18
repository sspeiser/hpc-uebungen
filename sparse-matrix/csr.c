#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_rows;
    int n_cols;
    int n_values;   // Number of non-zero values
    double *values;
    int *col_ind;
    int *row_ptr;
} CSR;

CSR* matrix_to_csr(int n_rows, int n_cols, double matrix[n_rows][n_cols])  {
    CSR* csr = malloc(sizeof(CSR));
    // todo
    //
    return csr;
}

double* csr_times_vector(CSR* csr, int n_vector, double vector[n_vector]) {
    double* result = malloc(sizeof(double) * csr->n_rows);
    // todo
    //
    return result;
}


int main(int argc, char *argv[]) {
    double matrix[4][5] = 
        {{1, 4, 0, 0, 1},
         {0, 0, 0, 0, 0},
         {0, 5, 6, 0, 0},
         {0, 0, 3, 0, 0}};
    int n_rows = 4;
    int n_cols = 5;

    CSR* matrix_csr = matrix_to_csr(n_rows, n_cols, matrix);

    double vector[5] = {3, 4, 5, 6, 7};
}
