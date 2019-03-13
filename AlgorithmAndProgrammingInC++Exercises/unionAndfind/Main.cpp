#include <iostream>
#include <vector>
using namespace std;

// ================= 代码实现开始 =================

const int N = 300005;

int Father[N], Rank[N];
//find with path compress
int find(int x) {
    if (x!=Father[x]) {
        Father[x] = find(Father[x]);
    }
    return Father[x];
}

// 给定n个变量以及m个约束，判定是否能找出一种赋值方案满足这m个约束条件
// n：如题意
// m：如题意
// A：大小为m的数组，表示m条约束中的a
// B：大小为m的数组，表示m条约束中的b
// E：大小为m的数组，表示m条约束中的e
// 返回值：若能找出一种方案，返回"Yes"；否则返回"No"（不包括引号）。
string getAnswer(int n, int m, vector<int> A, vector<int> B, vector<int> E) {
    for (int i = 0; i <= n; ++i) {
        Father[i] = i;
        Rank[i] = 0;
    }

    int head = 0;
    int tail = m-1;
    while (true) {
        while (E[head] != 0 && head < tail) ++ head;
        while (E[tail] != 1 && head < tail) -- tail;
        if (head >= tail) break;
        swap(E[head], E[tail]);
        swap(A[head], A[tail]);
        swap(B[head], B[tail]);
    }

    //for (int i = 0; i < m; ++i) cout << A[i] << " " << B[i] << " " << E[i] << endl;

    for (int i = 0; i < m; ++i)
    {
        int setA = find(A[i]);
        int setB = find(B[i]);
        if (E[i] == 0) {
            if (setA == setB)
                return "No";
        } else {
            if (setA != setB) {
                if (Rank[setA] < Rank[setB]) {
                    Father[setA] = setB;
                }
                else if (Rank[setB] < Rank[setA]) {
                    Father[setB] = setA;
                }
                else {
                    Rank[setA] = Rank[setA] + 1;
                    Father[setB] = setA;
                }
            }
        }
    }
    return "Yes";
}

// ================= 代码实现结束 =================

int main() {
    int T;
    for (scanf("%d", &T); T--; ) {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<int> A, B, E;
        for (int i = 0; i < m; ++i) {
            int a, b, e;
            scanf("%d%d%d", &a, &b, &e);
            A.push_back(a);
            B.push_back(b);
            E.push_back(e);
        }
        printf("%s\n", getAnswer(n, m, A, B, E).c_str());
    }
    return 0;
}
