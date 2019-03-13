#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ================= 代码实现开始 =================

const int N = 500005;

struct UnionSet {
    int f[N];

    void init(int n) {
        for (int i = 0; i < n; ++i)
            f[i] = i;
    }

    int find(int x) {
        if (f[x]!=x) {
            f[x] = find(f[x]);
        }
        return f[x];
    }

    bool merge(int x, int y) {
        int rootX = find(x-1);
        int rootY = find(y-1);
        if (rootX != rootY) {
            f[rootX] = rootY;
            return true;
        } else {
            return false;
        }
    }
} us;

// 给定一个n个点m条边的无向图，第i条边边权为i，求所有需要升级的边
// n：如题意
// m：如题意
// U：大小为m的数组，表示m条边的其中一个端点
// V：大小为m的数组，表示m条边的另一个端点
// 返回值：所有需要升级的边，从小到大排列；第一小问的答案自然即为返回值的size，所以你不必考虑如何返回size
vector<int> getAnswer(int n, int m, vector<int> U, vector<int> V) {
    vector<int> ans;
    us.init(n);
    for (int i = m-1; i >= 0 ; -- i) {
        if (us.merge(U[i], V[i]))
            ans.push_back(i+1);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// ================= 代码实现结束 =================

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> U, V;
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        U.push_back(u);
        V.push_back(v);
    }
    vector<int> ans = getAnswer(n, m, U, V);
    printf("%d\n", int(ans.size()));
    for (int i = 0; i < int(ans.size()); ++i)
        printf("%d\n", ans[i]);
    return 0;
}
