#include <iostream>
#include <vector>
using namespace std;

// ================= 代码实现开始 =================

/* 请在这里定义你需要的全局变量 */

// 这是进行排序的函数
// n：题目描述中的 n
// A：各同学的算法训练营成绩
// DS：各同学的数据结构训练营成绩
// 返回值：将要输出的数字依次加入到返回值的数组中
vector<int> getAnswer(int n, vector<int> A, vector<int> DS) {
    vector<int> sum, id;
    vector<int> ans;
    for (int i = 0; i < n; ++ i) {
        id.push_back(i+1);
        sum.push_back(A[i]+DS[i]);
    }
    int cnt = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = n-1; j > 0; -- j) {
            if (sum[j-1] < sum[j] || (sum[j] == sum[j-1] && A[j-1] < A[j])) {
                swap(id[j], id[j-1]);
                swap(sum[j], sum[j-1]);
                swap(A[j], A[j-1]);
                swap(DS[j], DS[j-1]);
                ++ cnt;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        ans.push_back(id[i]);
        ans.push_back(sum[i]);
        ans.push_back(A[i]);
        ans.push_back(DS[i]);
    }
    ans.push_back(cnt);
    return ans;
}

// ================= 代码实现结束 =================

int main() {
    int n;
    scanf("%d", &n);
    vector<int> A, DS;
    for (int i = 0; i < n; ++i) {
        int a, ds;
        scanf("%d%d", &a, &ds);
        A.push_back(a);
        DS.push_back(ds);
    }
    vector<int> ans = getAnswer(n, A, DS);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        printf("%d %d %d %d\n", ans[cnt], ans[cnt + 1], ans[cnt + 2], ans[cnt + 3]);
        cnt += 4;
    }
    printf("%d\n", ans[cnt]);
    return 0;
}
