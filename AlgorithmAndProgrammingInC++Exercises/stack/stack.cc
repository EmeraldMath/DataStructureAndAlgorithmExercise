#include <iostream>
#include <string>
using namespace std;

class stack {
    int size;
    string* stk;
  public:
    stack(string* arr, int& s) {
      size = s;
      stk = arr;
    }
    void push(string& e) {
      stk[size] = e;
      ++ size;
    }
    string pop() {
      return stk[-- size];
    }
    string query(int y) {
      return stk[y-1];
    }
};

int main() {
  string arr[100000];
  int size = 0;
  stack stk(arr, size);
  int i;
  cin >> i;
  for (int j = 0; j < i; ++ j) {
    int in;
    cin >> in;
    if (in == 1) {
      string c;
      cin >> c;
      stk.push(c);
    }
    if (in == 2) cout << stk.pop() << endl;
    if (in == 3) {
      int y;
      cin >> y;
      cout << stk.query(y) << endl;
    }
  }

  return 0;
}
