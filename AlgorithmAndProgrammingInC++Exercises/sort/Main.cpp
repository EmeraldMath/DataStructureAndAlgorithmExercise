#include <iostream>
#include <vector>
using namespace std;

// ================= 代码实现开始 =================
void merge(vector<int> l, vector<int> r, vector<int>& ans) {
    vector<int>::iterator lt = l.begin();
    vector<int>::iterator rt = r.begin();
    while(lt != l.end() && rt != r.end()) {
        if (*lt < *rt) {
            ans.push_back(*lt);
            ++ lt;
        } else {
            ans.push_back(*rt);
            ++ rt;
        }
    }
    if (lt == l.end()) {
        for (; rt != r.end(); ++ rt) ans.push_back(*rt);
    }
    else if (rt == r.end()) {
        for(; lt != l.end(); ++ lt) ans.push_back(*lt);
    }
}

vector<int> mergeSort(int lo, int hi, vector<int> a) {
    vector<int> ans;
    if (hi-lo == 1) {
        ans.push_back(a[lo]);
        return ans;
    }
    int mi = (lo+hi) >> 1;
    vector<int> l = mergeSort(lo, mi, a);
    vector<int> r = mergeSort(mi, hi, a);
    merge(l, r, ans);
    return ans;
}

// 将给定数组a升序排序
// n：数组大小
// a：所给数组，大小为n
// 返回值：排序后的数组
vector<int> getAnswer(int n, vector<int> a) {
    return mergeSort(0, n, a);
}

// ================= 代码实现结束 =================

int main() {
    int n;
    scanf("%d", &n);
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        a.push_back(x);
    }
    a = getAnswer(n, a);
    for (int i = 0; i < n; ++i)
        printf("%d%c", a[i], " \n"[i == n - 1]);
    return 0;
}
