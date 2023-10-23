#include <stdio.h>
#include <stdlib.h>

//Input a matrix

double* input_matrix(int* rows, int* columns, const char* matrix_name) {
    printf("Enter the number of rows and columns for %s:\n", matrix_name);
    scanf("%d %d", rows, columns);

    if (*rows <= 0 || *columns <= 0) {
        printf("Invalid dimensions for %s\n", matrix_name);
        return NULL;
    }

    double* matrix = (double*)malloc((*rows) * (*columns) * sizeof(double));

    if (matrix == NULL) {
        printf("Memory allocation failed for %s\n", matrix_name);
        return NULL;
    }

    printf("Enter values for %s in row-major order:\n", matrix_name);
    for (int i = 0; i < (*rows) * (*columns); i++) {
        scanf("%lf", &matrix[i]);
    }

    return matrix;
}

//Multiply two matrices
int matrix_multiply(const double* m1, int m1_rows, int m1_columns, const double* m2, int m2_rows, int m2_columns, double* result) {
    if (m1_columns != m2_rows) {
        printf("Matrix dimensions are not suitable for multiplication.\n");
        return 0;  // Return 0 to indicate failure
    }

    for (int i = 0; i < m1_rows; i++) {
        for (int j = 0; j < m2_columns; j++) {
            result[i * m2_columns + j] = 0.0;
            for (int k = 0; k < m1_columns; k++) {
                result[i * m2_columns + j] += m1[i * m1_columns + k] * m2[k * m2_columns + j];
            }
        }
    }

    return 1;  // Return 1 to indicate success
}

//Output a matrix
void output_matrix(const double* matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%lf ", matrix[i * columns + j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void) {
    double* m1;
    double* m2;
    double* m3;
    int m1_rows, m1_columns, m2_rows, m2_columns;

    if (((m1 = input_matrix(&m1_rows, &m1_columns, "Matrix 1")) != NULL) &&
        ((m2 = input_matrix(&m2_rows, &m2_columns, "Matrix 2")) != NULL) &&
        ((m3 = malloc(m1_rows * m2_columns * sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1, m1_rows, m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2, m2_rows, m2_columns);
        if (matrix_multiply(m1, m1_rows, m1_columns, m2, m2_rows, m2_columns, m3)) {
            printf("Product\n");
            output_matrix(m3, m1_rows, m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return (0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return (-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return (-2);
    }
}
