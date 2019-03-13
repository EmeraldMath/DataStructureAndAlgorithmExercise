#include <cmath>
#include <iostream>
#include <random>
#include <chrono>
#include "mpi.h"
#include <sstream>
#include <mkl.h>
#include <ctime>
int main(int argc, char *argv[]) {
  int N;
  int iter;
  int myid;
  int count;
  int sum;
  int num_procs;
  double start, end;
  double x, y, z, r;
  VSLStreamStatePtr rnStream;
  vslNewStream(&rnStream, VSL_BRNG_MT19937, time(0));
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  MPI_Barrier(MPI_COMM_WORLD);
  start = MPI_Wtime();
  count = 0;
  if (myid == 0) {std::string ss(argv[1]); N = std::stoi(ss);}
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
  double *xv = new double[N];
  double *yv = new double[N];
  double *zv = new double[N];
  double left = 0.0;
  double right = 1.0;
  vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rnStream, N, xv, left, right);
  vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rnStream, N, yv, left, right);
  vdRngUniform(VSL_RNG_METHOD_UNIFORM_STD, rnStream, N, zv, left, right);
  for (int i = 0; i < N; ++ i) {
    x = xv[i];
    y = yv[i];
    z = zv[i];
    r = x*x + y*y + z*z;//(3x)^2/(3^2) + (4y)^2/(4^2) + (5z)^2/(5^2) = x^2 + y^2 + z^2;
    if (r < 1) {
        ++ count;
    }
  }
  
  MPI_Reduce(&count, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (myid == 0) {
    double Pi = 3.14159265358979323846;
    double a = 3.0;
    double b = 4.0;
    double c = 5.0;
    //double pi = 6.0*sum/(num_procs*N);
    double my_vol = 1.0*sum/(num_procs*N)*a*b*c*8;
    double tr_vol = 4.0/3.0*Pi*a*b*c;
    //std::cout << "sum :" << sum << std::endl;
    //std::cout << "num_procs :" << num_procs << std::endl;
    std::cout << "my volume - true volume = " << my_vol << " - " << tr_vol << " = " << my_vol - tr_vol << std::endl;
  }
  delete[] xv;
  delete[] yv;
  delete[] zv;
  MPI_Barrier(MPI_COMM_WORLD);
  end = MPI_Wtime();
  MPI_Finalize();
  if (myid == 0) {
  std::cout << "elapsed time: " << end-start << " seconds" << std::endl;
  }
  return 0;
}
