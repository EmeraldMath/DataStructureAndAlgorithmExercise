#include <stdio.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include <cstring>
using namespace std;

// ================= 代码实现开始 =================

typedef double lf;
typedef long long ll;

const int N = 300005;

// 用于存储一个二维平面上的点
struct ip {
    int x, y;
    
    // 构造函数
    ip(int x = 0, int y = 0) : x(x), y(y) { }
    
     // 先比较x轴，再比较y轴
    bool operator < (const ip &a) const {
        return x == a.x ? y < a.y : x < a.x;
    }
} a[N], b[N];

bool compy(const ip &a, const ip &b) {
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}

// 计算x的平方
ll sqr(const ll &x) {
    return x * x;
}

// 计算点a和点b的距离
lf dis(const ip &a, const ip &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

//lf ans;

lf solve(int l, int r) {
        lf ans = 1e100;
        if (r == l) return ans;
	if (r - l == 1) {
	   ans = dis(a[l], a[r]);
           return ans;
	}

	int mid = (l + r) >> 1;
	lf ans1 = solve(l, mid);
	lf ans2 = solve(mid + 1, r);
        ans = min(ans1, ans2);
	int md = a[mid].x;
	int cnt = 0;
	for (int i = l; i <= r; ++ i) {
	    if (fabs(a[i].x - md) <= ans)
	        b[cnt++] = a[i];
	}
	sort(b, b + cnt, compy);
	for (int i = 0; i < cnt; ++i)
	    for (int j = i + 1; j < cnt && b[j].y - b[i].y <= ans; ++j)
		ans = min(ans, dis(b[i], b[j]));
        return ans;
}

// 计算最近点对的距离
// n：n个点
// X, Y：分别表示x轴坐标和y轴坐标，下标从0开始
// 返回值：最近的距离
double getAnswer(int n, vector<int> X, vector<int> Y) {
    for (int i = 0; i < n; ++i)
    	a[i + 1] = ip(X[i], Y[i]);
    //lf ans = 1e100;
    sort(a + 1, a + 1 + n);
    lf ans = solve(1, n);
    return ans;
}

// ================= 代码实现结束 =================

int main() {
    int n;
    scanf("%d", &n);
    vector<int> X, Y;
    for (int i = 1; i <= n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        X.push_back(x);
        Y.push_back(y);
    }
    printf("%.2f\n", getAnswer(n, X, Y));
    return 0;
}

