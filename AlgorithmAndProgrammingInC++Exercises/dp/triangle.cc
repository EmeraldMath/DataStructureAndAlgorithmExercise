#include <iostream>
using namespace std;

const int N = 1005;
int table[N][N];

int getIn(int n) {
  int sum = 0;
  for (int i = 1; i < n+1; ++ i)
    for (int j = 1; j < i+1; ++ j) {
      int a;
      cin >> a;
      table[i][j] = a + max(table[i-1][j-1], table[i-1][j]);
    }

  for (int i = 1; i < n+1; ++ i) sum = sum < table[n][i] ? table[n][i] : sum;
  return sum;
}

int main() {
  int n;
  cin >> n;
  cout << getIn(n) << endl;
  return 0;
}