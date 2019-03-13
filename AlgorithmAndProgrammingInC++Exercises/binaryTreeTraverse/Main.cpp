//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

// ================= 代码实现开始 =================

const int N = 100005;

struct node {
    int val, l, r;
    node() {
        val = 0;
        l = 0;
        r =0;
    }
} t[N];

int root, cnt;

int insert(int v, int& x) {
    if (x == 0) {
        x = ++ cnt;
        t[x].val = v;
        return x;
    }
    if (v < t[x].val) {
        t[x].l = insert(v, t[x].l);
    } else {
        t[x].r = insert(v, t[x].r);
    }
    return x;
}

void dlr(int x, vector<int> &ans) {
    if (x) {
        ans.push_back(t[x].val);
        dlr(t[x].l, ans);
        dlr(t[x].r, ans);
    }
    return;
}

void lrd(int x, vector<int> &ans) {
    if (x) {
        lrd(t[x].l, ans);
        lrd(t[x].r, ans);
        ans.push_back(t[x].val);
    }
    return;
}
// 给定一个1到n的排列，依次插入到二叉树中，返回前序遍历和后序遍历
// n：如题意
// sequence：给定的排列，大小为n
// 返回值：将要输出的元素依次加入到返回值中
vector<int> getAnswer(int n, vector<int> sequence) {
    root = cnt = 0;

    for (int i = 0; i < int(sequence.size()); ++i)
        root = insert(sequence[i],root);

    vector<int> ans;
    dlr(root, ans);
    lrd(root, ans);
    return ans;
}

// ================= 代码实现结束 =================

int main() {
    int n;
    scanf("%d", &n);
    vector<int> sequence;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        sequence.push_back(x);
    }
    vector<int> ans = getAnswer(n, sequence);
    for (int i = 0; i < n; ++i)
        printf("%d%c", ans[i], " \n"[i == n - 1]);
    for (int i = 0; i < n; ++i)
        printf("%d%c", ans[n + i], " \n"[i == n - 1]);
    return 0;
}
