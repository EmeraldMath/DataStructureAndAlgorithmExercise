#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// ================= 代码实现开始 =================

typedef long long ll;

priority_queue<ll, vector<ll>, greater<ll> > pq;

// 这是求解整个问题的函数
// w：题目描述中的 w（所有）
// n：题目描述中的 n
// 返回值：答案
long long getAnswer(int n, vector<long long> w) {
    for (int i = 0; i < n; ++i)
        pq.push(w[i]);
    ll sum = 0;
    while (pq.size() > 1) {
        ll newEle = 0;
        for (int k = 0; k < 2; ++k) {
            newEle = pq.top() + newEle;
            pq.pop();
        }
        pq.push(newEle);
        sum += newEle;
    }
    return sum;
}

// ================= 代码实现结束 =================

int main() {
    int n;
    scanf("%d", &n);
    vector<long long> w;
    for (int i = 0; i < n; ++i) {
        long long x;
        scanf("%lld", &x);
        w.push_back(x);
    }
    printf("%lld\n", getAnswer(n, w));
    return 0;
}
