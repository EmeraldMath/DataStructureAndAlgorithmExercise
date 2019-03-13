#ifndef FUN_H
#define FUN_H

void print_mat(int rank, int size, int n, int N, double** mat);

void print_vec(int rank, int size, double* vect, int n);

void vec_norm(double *x, int n);

void vec_norm2(double* x, double* x_t, double* y, int n);

void mat_vec(int rank, int size, double* y, double** mat, double* x, double* x_t, int N, MPI_Request reqs[2], MPI_Status stats[2]);



#endif
