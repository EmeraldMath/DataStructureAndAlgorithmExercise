#include <iostream>
#include <mpi.h>
#include <cstdlib>
#include <random>
#include <sstream>

int main(int argc, char *argv[]) {
    double t1, t2;
    std::istringstream iss(argv[1]);
    int N;
    iss >> N;
    int n_i, n_j, nmax, n_send; 
    int rank, size, atom_i, atom_j;
    double atom[4];
    int charge[6] = {-3,-2,-1,1,2,3};
    double *x_i, *y_i, *z_i, *x_j, *y_j, *z_j;
    double *tx, *ty, *tz;
    int *q_i, *q_j, *tq;
    std::random_device ird;
    std::mt19937 igen(ird());
    std::uniform_int_distribution<> idis(1,6);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-6.0, 6.0);
    MPI_Request reqs[10];
    MPI_Status stats[10];
    MPI_Init(&argc, &argv);
    t1 = MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size > 1 && rank != size-1) {
    	n_i = N/size;
        n_j = n_i;
        nmax = N - N/size*(size-1);
    	x_i = new double[nmax];
        y_i = new double[nmax];
        z_i = new double[nmax];
        q_i = new int[nmax];
        x_j = new double[nmax];
        y_j = new double[nmax];
        z_j = new double[nmax];
        q_j = new int[nmax];
        tx = new double[nmax];
        ty = new double[nmax];
        tz = new double[nmax];
        tq = new int[nmax];
        for (int i = 0; i < n_i; ++ i) {
            x_i[i] = dis(gen);
            y_i[i] = dis(gen);
            z_i[i] = dis(gen);
            q_i[i] = charge[idis(igen)-1];
            x_j[i] = x_i[i];
            y_j[i] = y_i[i];
            z_j[i] = z_i[i];
            q_j[i] = q_i[i];
        }
    } 
    if (rank == size - 1) {
    	n_i = N - N/size*(size-1);
        n_j = n_i;
        nmax = n_i;
    	x_i = new double[nmax];
        y_i = new double[nmax];
        z_i = new double[nmax];
        q_i = new int[nmax];
        x_j = new double[nmax];
        y_j = new double[nmax];
        z_j = new double[nmax];
        q_j = new int[nmax];
        tx = new double[nmax];
        ty = new double[nmax];
        tz = new double[nmax];
        tq = new int[nmax];
        for (int i = 0; i < n_i; ++ i) {
            x_i[i] = dis(gen);
            y_i[i] = dis(gen);
            z_i[i] = dis(gen);
            q_i[i] = charge[idis(igen)-1];
            x_j[i] = x_i[i];
            y_j[i] = y_i[i];
            z_j[i] = z_i[i];
            q_j[i] = q_i[i];
        }
    }
/*
    for (int i = 0; i < n_i; ++ i)
      printf("process %d has particles (%f, %f, %f), %d\n", rank, x_i[i], y_i[i], z_i[i], q_i[i]);
*/
   for (int k = 0; k < size; ++k)
   {
    //calculate the interactions
       for (int i = 0; i < n_i; ++i)
       {
           for (int j = 0; j < n_j; ++j)
           {
               int atom_i = rank*(N/size) + i;
               int atom_j = (rank+k)%size*(N/size) + j;
               double r = sqrt((x_i[i]-x_j[j])*(x_i[i]-x_j[j])
                              +(y_i[i]-y_j[j])*(y_i[i]-y_j[j])
                              +(z_i[i]-z_j[j])*(z_i[i]-z_j[j]));
               if (r == 0) {
                    //printf("process: %d, F(i=%d,j=%d)=(%f, %f, %f)\n",rank, atom_i,atom_j,r,r,r);
               }
               else {
                    double scale = (q_i[i] * q_j[j] * 1.0)/(r*r*r);
                    double r_x = scale * (x_i[i] - x_j[j]);
                    double r_y = scale * (y_i[i] - y_j[j]);
                    double r_z = scale * (z_i[i] - z_j[j]);
                    //printf("process: %d, F(i=%d,j=%d)=(%f, %f, %f)\n",rank, atom_i,atom_j,r_x,r_y,r_z);
               }
               tx[j] = x_j[j];
               ty[j] = y_j[j];
               tz[j] = z_j[j];
               tq[j] = q_j[j];
            }
        }
       //ratate
        if (size < 2) break; 
        n_send = n_j;
        MPI_Irecv(&n_j, 1, MPI_INT, (rank-1+size)%size, 0, MPI_COMM_WORLD, &reqs[0]);
        MPI_Irecv(x_j, nmax, MPI_DOUBLE, (rank-1+size)%size, 0, MPI_COMM_WORLD, &reqs[1]);
        MPI_Irecv(y_j, nmax, MPI_DOUBLE, (rank-1+size)%size, 0, MPI_COMM_WORLD, &reqs[2]);
        MPI_Irecv(z_j, nmax, MPI_DOUBLE, (rank-1+size)%size, 0, MPI_COMM_WORLD, &reqs[3]);
        MPI_Irecv(q_j, nmax, MPI_INT, (rank-1+size)%size, 0, MPI_COMM_WORLD, &reqs[4]);
        MPI_Isend(&n_send, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD, &reqs[5]);
        MPI_Isend(tx, nmax, MPI_DOUBLE, (rank+1)%size, 0, MPI_COMM_WORLD, &reqs[6]);
        MPI_Isend(ty, nmax, MPI_DOUBLE, (rank+1)%size, 0, MPI_COMM_WORLD, &reqs[7]);
        MPI_Isend(tz, nmax, MPI_DOUBLE, (rank+1)%size, 0, MPI_COMM_WORLD, &reqs[8]);
        MPI_Isend(tq, nmax, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD, &reqs[9]);
        MPI_Waitall(10, reqs, stats);
        //printf("Process %d has recerived %d from process %d\n", rank, n_j, rank-1);
        
        
    }


    t2 = MPI_Wtime();
    printf("Process: %d, Elapsed time is %fs\n", rank, t2-t1);
    MPI_Finalize();
    if (rank == 0) printf("N: %d\n", N);
    
    return 0;
}
