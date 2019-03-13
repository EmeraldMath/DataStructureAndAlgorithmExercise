#include <mpi.h>
#include <iostream>
#include <random>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include "fun.h"

int main(int argc, char *argv[]) {
    double t1, t2;
    std::istringstream iss(argv[1]);
    std::string fname(argv[2]);
    int N, n;
    iss >> N;
    std::ifstream infile;
    int size, rank; 
    
    MPI_Request req[2];
    MPI_Status stats[2];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    n = N/size;
    double** mat = new double*[n];
    for (int i = 0; i < n; ++ i) {
        mat[i] = new double[N];
    }

    if (rank == 0) {
        infile.open(fname.c_str());
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < N; ++ j) {
                infile >> mat[i][j];
            }     
        }
        double* inmat = new double[N];
        for (int i = 1; i < size; ++ i) {
            for (int j = 0; j < n; ++ j) {
                for (int k = 0; k < N; ++ k) {
                    infile >> inmat[k];
                }
                MPI_Send(inmat, N, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            }
        } 
    } else {
      for (int j = 0; j < n; ++ j)
          MPI_Recv(mat[j], N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    print_mat(rank, size, n, N, mat);
     
    t1 = MPI_Wtime();
    //int MAX_ITER = 30;
    int MAX_ITER = 2;
    bool flag = false;
    int it = 0;

    double* y = new double[n];
    double* x = new double[n];
    double* x_t = new double[n];
    double yy_yx[2] = {0,0};
    double ydoty_x[2] = {0,0};
    double eigenv = 0;
    double old_eigenv = -1000000;
    double diff = 100;
    for (int i = 0; i < n; ++ i) {
        y[i] = 0;
        x_t[i] = 1;
    }
    //std::cout << "x" << std::endl;
    //print_vec(rank, size, x, n);
    vec_norm(x_t, n);
    //if (rank == 0) std::cout << "norm x" << std::endl;
    //print_vec(rank, size, x_t, n);
    //for (int i_loop = 0; i_loop < MAX_ITER; i_loop++) {
    while (true) {
        //
        //x = norm(x_t) in mat_vec
        //
        mat_vec(rank, size, y, mat, x, x_t, N, req, stats);
        //print_vec(rank, size, x, n);
        //if (rank == 0) std::cout << "y" << std::endl;
        //print_vec(rank, size, y, n);
        //sety=x;
        yy_yx[0] = 0;
        yy_yx[1] = 0;
        for (int i = 0; i < n; ++ i) {
            yy_yx[0] += y[i] * y[i];
            yy_yx[1] += y[i] * x[i]; 
        }

        //if (rank == 0) std::cout << "yy_yx 1" << std::endl;
        //print_vec(rank, size, yy_yx, 2);

        MPI_Allreduce(&yy_yx, &ydoty_x, 2, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        
        //if (rank == 0) std::cout << "ydoty_x 2" << std::endl;
        //print_vec(rank, size, ydoty_x, 2);
        
        if (ydoty_x[1] == 0) {
            flag = true;
            if (rank == 0) std::cout << "it " << it << " diff " << diff << " eigenv " << eigenv << std::endl;
            break;
        }       
        eigenv = ydoty_x[0]/ydoty_x[1];
        
        diff = eigenv - old_eigenv;
        old_eigenv = eigenv;
        it ++;

        if (diff < 1e-6 && diff > -1e-6) {
            if (rank == 0) std::cout << "it " << it << " diff " << diff << " eigenv " << eigenv << std::endl;
           //diff = 0;
           break;
        }
        vec_norm2(x, x_t, y, n);
        //if (rank == 0) std::cout << "new x = norm y" << std::endl;
        //print_vec(rank, size, x, n);
        //if (rank == 0) std::cout << "new x_t = norm y" << std::endl;
        //print_vec(rank, size, x_t, n);
    }

    //if (diff != 0) {

    //}

    vec_norm(y, n);
    t2 = MPI_Wtime();
    double etime = t2 - t1;
    double maxt;
    MPI_Reduce(&etime, &maxt, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    if (rank != 0) {
        MPI_Send(y, n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    else {
        if (flag) {
            std::cout << "eigen value is zero" << std::endl;
            std::cout << "elapsed time: " << maxt << std::endl;
        } else {
            std::cout << "eigen value = " << eigenv << std::endl;
            std::cout << "eigen vector = [ ";
            for (int i = 0; i < n; ++ i)
                std::cout << y[i] << " ";
            for (int i = 1; i < size; ++ i) {
                MPI_Recv(y, n, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int j = 0; j < n; ++ j)
                    std::cout << y[j] << " ";
            }
            std::cout << "]" << std::endl;
            std::cout << "elapsed time: " << maxt << std::endl;
            std::cout << "diff & it: " << diff << " " << it << std::endl;
        }
    }
    
    MPI_Finalize();
    return 0;
}
