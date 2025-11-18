#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_rows;
    int n_cols;
    int n_values;   // Number of non-zero values
    double *values; // length = n_values
    int *col_ind;   // length = n_values
    int *row_ptr;   // length = n_rows + 1
} CSR;

/**
 * Convert a dense matrix to CSR format.
 *
 * @param n_rows   Number of rows in the matrix
 * @param n_cols   Number of columns in the matrix
 * @param matrix   Pointer to the matrix (flattened 1D array, row-major)
 * @return Pointer to a newly allocated CSR struct, or NULL on error.
 *         Caller is responsible for freeing the struct and its arrays.
 */
CSR* matrix_to_csr(int n_rows, int n_cols, const double* matrix) {
    if (!matrix || n_rows <= 0 || n_cols <= 0) return NULL;

    // Count non-zero values
    int n_values = 0;
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            if (matrix[i * n_cols + j] != 0.0) n_values++;
        }
    }

    CSR* csr = malloc(sizeof(CSR));
    if (!csr) return NULL;

    csr->n_rows = n_rows;
    csr->n_cols = n_cols;
    csr->n_values = n_values;

    csr->values = malloc(sizeof(double) * n_values);
    csr->col_ind = malloc(sizeof(int) * n_values);
    csr->row_ptr = malloc(sizeof(int) * (n_rows + 1));

    if (!csr->values || !csr->col_ind || !csr->row_ptr) {
        free(csr->values);
        free(csr->col_ind);
        free(csr->row_ptr);
        free(csr);
        return NULL;
    }

    int k = 0;
    for (int i = 0; i < n_rows; i++) {
        csr->row_ptr[i] = k;
        for (int j = 0; j < n_cols; j++) {
            double val = matrix[i * n_cols + j];
            if (val != 0.0) {
                csr->values[k] = val;
                csr->col_ind[k] = j;
                k++;
            }
        }
    }
    csr->row_ptr[n_rows] = k; // end of last row

    return csr;
}

/**
 * Free a CSR struct allocated by matrix_to_csr
 */
void free_csr(CSR* csr) {
    if (!csr) return;
    free(csr->values);
    free(csr->col_ind);
    free(csr->row_ptr);
    free(csr);
}

/**
 * Multiplies a CSR matrix by a vector.
 * 
 * @param csr       Pointer to CSR matrix (read-only)
 * @param vector    Pointer to input vector
 * @param n_vector  Number of elements in vector
 * @param result    Pointer to pre-allocated result array
 * @param n_result  Number of elements allocated in result array
 * @return 0 on success, -1 if size mismatch
 */
int csr_times_vector(const CSR* csr, const double* vector, int n_vector,
                     double* result, int n_result) {
    if (!csr || !vector || !result) return -1; // sanity check
    if (n_vector != csr->n_cols) return -1;    // vector length mismatch
    if (n_result != csr->n_rows) return -1;    // result length mismatch

    for (int i = 0; i < csr->n_rows; i++) {
        double sum = 0;
        for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
            sum += csr->values[j] * vector[csr->col_ind[j]];
        }
        result[i] = sum;
    }

    return 0; // success
}

int main(void) {
    double matrix[4 * 5] = {
        1, 4, 0, 0, 1,
        0, 0, 0, 0, 0,
        0, 5, 6, 0, 0,
        0, 0, 3, 0, 0
    };

    CSR* csr = matrix_to_csr(4, 5, matrix);
    if (!csr) return 1;

    double vector[5] = {3, 4, 5, 6, 7};
    double result[4];

    int status = csr_times_vector(csr, vector, 5, result, 4);
    if (status != 0) {
        printf("Size mismatch!\n");
        free_csr(csr);
        return 1;
    }

    for (int i = 0; i < 4; i++) printf("%f\n", result[i]);

    free_csr(csr);
    return 0;
}
