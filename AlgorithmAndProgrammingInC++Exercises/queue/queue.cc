#include <iostream>
using namespace std;

class queue {
  string* q;
  int size;
  int first;
  int last;
  public:
    queue(string* qu, int s) {
      q = qu;
      size = s;
      first = 0;
      last = 0;
    }
    void enqueue(string& s) { q[last ++] = s; }
    void dequeue() { cout << q[first++] << endl; }
    void query(int& y) { cout << q[first+y-1] << endl;}
};

int main() {
  string str[100000];
  int size = 0;
  queue q(str, size);
  int n;
  cin >> n;
  for (int i = 0; i < n; ++ i) {
    int j;
    cin >> j;
    if (j == 1) {
      string s;
      cin >> s;
      q.enqueue(s);
    }
    if (j == 2) q.dequeue();
    if (j == 3) {
      int y;
      cin >> y;
      q.query(y);
    }
  }
  return 0;
}