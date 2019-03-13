#include <iostream>
#include <random>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>

double**  mat_gen(std::mt19937 gen1, std::uniform_real_distribution<> dis1,std::mt19937 gen,std::uniform_real_distribution<> dis, int N);
void print(std::ofstream& fout, double** buf, int N);

int main(int argc, char *argv[]) {
    double t1, t2;
    std::istringstream iss(argv[1]);
    int N;
    iss >> N;
    int rank, size;
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_real_distribution<> dis1(0,1);	
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0,10);
    std::ofstream fout;
    std::string fname(argv[2]);
     
    fout.open(fname.c_str());
    double** mat =  mat_gen(gen1, dis1, gen, dis, N);
    print(fout, mat, N);
    fout.close();

    return 0;
}

double**  mat_gen(std::mt19937 gen1, std::uniform_real_distribution<> dis1,std::mt19937 gen,std::uniform_real_distribution<> dis,int N) {
    double** mat = new double*[N];
    for (int i = 0; i < N; ++ i) {
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

void print(std::ofstream& fout, double** buf, int N) {
    for (int j = 0; j < N; ++ j) {
        for (int k = 0; k < N; ++ k)
            fout << std::setw(12) << buf[j][k];
        fout << std::endl;
    }
}

