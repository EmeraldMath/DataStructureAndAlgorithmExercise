#include <iostream>
#include <random>
#include <mpi.h>
#include <iomanip>
double**  mat_gen(std::mt19937 gen1, std::uniform_real_distribution<> dis1,std::mt19937 gen,std::uniform_real_distribution<> dis,int n,int N) {
    double** mat = new double*[n];
    for (int i = 0; i < n; ++ i) {
        mat[i] = new double[N];
        for (int j = 0; j < N; ++ j) {
            double p = dis1(gen1);
            if (p >= 0.05) {
                mat[i][j] = 0;
            }
            else {
                double q = dis(gen);
                while (q == 0) q = dis(gen);
                mat[i][j] = q;
            }
        }
    }
    return mat;
}

void print(double* buf, int n, int N) {
    for (int j = 0; j < n; ++ j) {
        for (int k = 0; k < N; ++ k)
            std::cout << std::setw(12) << buf[j*N+k];
        std::cout << std::endl;
    }
}

void print_mat(int rank, int size, int n, int N, double** mat) {
    double* buf = new double[n*N];
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < N; ++ j) {
            buf[i*N+j] = mat[i][j];
        }
    }
    if (rank == 0) {
        std::cout << "Process: " << rank << std::endl;
        print(buf, n, N);
        for (int i = 1; i < size; ++ i) {
            std::cout << "Process: " << i << std::endl;
            MPI_Recv(buf, n*N, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            print(buf, n, N);
        }
    } else {
        MPI_Send(buf, n*N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
}

void print_vec(int rank, int size, double* vec, int n) {
    double* buf = new double[n];
    if (rank == 0) {
        std::cout << "Process: " << rank << std::endl;
        print(vec, 1, n);
        for (int i = 1; i < size; ++ i) {
            std::cout << "Process: " << i << std::endl;
            MPI_Recv(buf, n, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            print(buf, 1, n);
        }
    } else {
        MPI_Send(vec, n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

}

void vec_norm(double* x, int n) {
    double d_tmp_t = 0.0;
    double d_tmp = 0.0;
    for (int i = 0; i < n; ++ i)
        d_tmp_t += x[i]*x[i];
    MPI_Allreduce(&d_tmp_t, &d_tmp, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    d_tmp = (d_tmp == 0 ? 0 : 1.0/sqrt(d_tmp));
    for (int i = 0; i < n; ++ i)
        x[i] = x[i] * d_tmp;
}

void vec_norm2(double* x, double* x_t, double* y, int n) {
    double d_tmp_t = 0.0;
    double d_tmp = 0.0;
    for (int i = 0; i < n; ++ i)
        d_tmp_t += y[i]*y[i];
    MPI_Allreduce(&d_tmp_t, &d_tmp, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    d_tmp = (d_tmp == 0 ? 0 : 1.0/sqrt(d_tmp));
    for (int i = 0; i < n; ++ i) {
        x[i] = y[i] * d_tmp;
        x_t[i] = x[i];
    }
}

void mat_vec(int rank, int size, double* y, double** mat, double* x, double* x_t, int N, MPI_Request reqs[2], MPI_Status stats[2]) {
    int n = N/size;
    for (int i = 0; i < n; ++ i) y[i] = 0;
    for (int r = 0; r < size; ++ r) {
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                x[j] = x_t[j];
                y[i] += mat[i][(r*n+(rank*n)+j)%N] * x[j];
                //if (rank == 0) std::cout << "mat " <<  mat[i][(r*n+(rank*n)+j)%N] << " x " <<  x[j] << std::endl;
            }
        }
        //if (rank == 0) std::cout << "r = " << r << std::endl;
        //print_vec(rank, size, x, n);
        //rotate
        if (size < 2) break;
        MPI_Irecv(x_t, n, MPI_DOUBLE, (rank+1)%size, 0, MPI_COMM_WORLD, &reqs[0]);
        MPI_Isend(x, n, MPI_DOUBLE, (rank-1+size)%size, 0, MPI_COMM_WORLD, &reqs[1]);
        MPI_Waitall(2, reqs, stats);
    }
    for (int j = 0; j < n; ++ j) x[j] = x_t[j];
}

