#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    int* A = new int[n];
    int* B = new int[n];
    int** M = new int*[n+1];
    for (int i = 0; i < n+1; ++ i) {
        M[i] = new int[n+1];
        for (int j = 0; j < n+1; ++ j)
            M[i][j] = 0;
    }
    for (int i = 1; i <= n; ++ i) {
        cin >> A[i];
    }
    for (int i = 1; i <= n; ++ i) cin >> B[i];
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= n; ++ j) {
            if (A[i] == B[j]) M[i][j] = M[i-1][j-1] + 1;
            else M[i][j] = max(M[i-1][j], M[i][j-1]);
        }
    }
    cout << M[n][n] << endl;
    delete[] A;
    delete[] B;
    for (int i = 0; i < n+1; ++ i) delete[] M[i];
    delete[] M;

    return 0;
}