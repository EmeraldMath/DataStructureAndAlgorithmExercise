#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int N = 2*50005;
int ans, a[N], sum[N];

int getAns(int n) {
    queue<int> myQ, yourQ;
    for (int i = 1; i <= 2*n; ++ i)
        a[i] == 0 ?  yourQ.push(i) : myQ.push(i);
   
    while (!myQ.empty() && !yourQ.empty()) {
        if (myQ.front() < yourQ.front()) { 
            yourQ.pop();
            myQ.pop();
            ++ ans;
        } else {
            yourQ.pop();
        }
    }
    return ans;
}


int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        int id;
        cin >> id;
        a[id] = 1;
    }
    cout << getAns(n) << endl;
}
