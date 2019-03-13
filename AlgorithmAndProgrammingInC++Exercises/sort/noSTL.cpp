#include <iostream>
#include <cstring>
using namespace std;

// ================= 代码实现开始 =================
const int N = 500005;
int a[N];
void merge(int lo, int mi, int hi, int* a) {
    int i = lo;
    int k = 0;
    int j = mi;
    int* bkp = new int[mi-lo];
    memcpy(bkp, &a[lo], sizeof(int)*(mi-lo));
    while(k < mi - lo &&  j < hi) {
        if (bkp[k] <= a[j]) {
            a[i++]=bkp[k++];
        } else {
            a[i++] = a[j++];
        }
    }
    if (j == hi && k < mi - lo) {
        for(; k < mi - lo; ) a[i++] = bkp[k++];
    }
    delete[] bkp;
}

void mergeSort(int lo, int hi, int* a) {
    if (hi-lo == 1) return;
    int mi = (lo+hi) >> 1;
    mergeSort(lo, mi, a);
    mergeSort(mi, hi, a);
    merge(lo, mi, hi, a);
    return;
}

// 将给定数组a升序排序
// n：数组大小
// a：所给数组，大小为n
// 返回值：排序后的数组
void getAnswer(int n, int* a) {
    mergeSort(0, n, a);
}

// ================= 代码实现结束 =================

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        a[i] = x;
    }
    getAnswer(n, a);
    for (int i = 0; i < n; ++i)
        printf("%d%c", a[i], " \n"[i == n - 1]);
    return 0;
}
