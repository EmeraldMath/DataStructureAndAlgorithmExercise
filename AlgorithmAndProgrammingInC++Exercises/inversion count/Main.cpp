#include <iostream>
#include <vector>
using namespace std;

// ================= 代码实现开始 =================

vector<int> seq, seqTemp;
long long cnt;

void mergeSort(long long l, long long r) {
	//cout << "l " << l << " r " << r << endl;
	if (r - l == 0) return;
	long long mid = (l + r) >> 1;
	mergeSort(l, mid);
	mergeSort(mid+1, r);
	long long p = l, q = mid + 1;
	//cout << "l " << l << " r " << r << " p " << p << " q " << q << endl;
	for (long long i = l; i <= r ; ++i) {
		//cout << "seq[" << i << "] " << seq[i] << " ";
		if (seq[p] < seq[q] && p <= mid && q <= r) {
			//cout << "seq[p] " << seq[p] << " seq[q] " << seq[q] << endl;
			seqTemp[i] = seq[p++];
		}
		else if (seq[p] > seq[q] && p <= mid && q <= r) {
			//cout << "seq[p] " << seq[p] << " seq[q] " << seq[q] << endl;
			seqTemp[i] = seq[q++];
			if (p != mid+1)
		    	cnt += mid + 1 - p;
		}
		else if (p <= mid && q > r)
			seqTemp[i] = seq[p++];
		else if (p > mid && q <= r)
			seqTemp[i] = seq[q++];
	}
	//cout << endl;
	for (long long i = l; i <= r; ++i) {
		seq[i] = seqTemp[i];
		//cout << seq[i] << " ";
	}
	//cout << endl;
}

// 这个函数的功能是计算答案（即最少花费的金钱）
// n：表示序列长度
// a：存储整个序列 a
// 返回值：最少花费的金钱（需要注意，返回值的类型为 64 位有符号整数）
long long getAnswer(int n, vector<int> a) {
	seq = a;
	seqTemp.resize(n);
	cnt = 0;
	mergeSort(0, n-1);
	return cnt;
}

// ================= 代码实现结束 =================

int main() {
    int n, tmp;
    vector<int> a;
    a.clear();
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &tmp);
        a.push_back(tmp);
    }
    long long ans = getAnswer(n, a);
    cout << ans << '\n';
    /*
	for (int i = 0; i < n; ++i)
		cout << seq[i] << " ";
	cout << endl;
    */
    return 0;
}
