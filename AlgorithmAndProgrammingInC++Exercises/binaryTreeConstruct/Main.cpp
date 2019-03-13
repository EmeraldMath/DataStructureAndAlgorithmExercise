#include <iostream>
#include <vector>
using namespace std;

// ================= 代码实现开始 =================
/* 请在这里定义你需要的全局变量 */
const int N = 100005;
struct node {
   	int val, l, r;
   	node() {
      val = 0;
      l = 0;
      r = 0;
   	}
 } t[N];

 int root, cnt;

 void insert(int v, int& x) {
    if (t[x].val == 0) {
      t[++ cnt].val = v;
      x = cnt;
      return;
    }
    root = 0;
    if (v < t[x].val) insert(v, t[x].l);
    else insert(v, t[x].r);
 }

 void dlr(int x, vector<int>& ans) {
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
  int x = root;
  for (int i = 0; i < int(sequence.size()); ++i) {
    insert(sequence[i], x);
  }
  vector<int> ans;
  dlr(1,ans);
  lrd(1,ans);
  /*
  for (int i = 0; i < n; ++i)
      printf("%d%c", ans[i], " \n"[i == n - 1]);
  for (int i = 0; i < n; ++i)
      printf("%d%c", ans[n + i], " \n"[i == n - 1]);
      */
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
