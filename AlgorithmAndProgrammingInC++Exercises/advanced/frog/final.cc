#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

typedef pair<int, int> pii;
const int N = 1005;
int a[N][N], ans, n;
pii p[N];

int main() {
	int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, s;
        cin >> x >> s;
        p[i] = make_pair(x,s);
    }
    for (int l = 0; l < 2; ++ l) {
    	sort(p, p + n);
	    for (int i = 0; i < n; ++i) {
	        a[i][i] = p[i].second;
	        for (int j = i + 1; j < n; ++j)
	        	a[j][i] = 0;
	    }
	    for (int i = 0; i < n; ++i) {
	        for (int j = i; j < n; ++j) {
	        	for (int k = j + 1; k < n; ++k) {
	        		if ((p[k].first - p[j].first) >= (p[j].first - p[i].first)) {
	        		    a[k][j] =  max(a[j][i] + p[k].second, a[k][j]);
	        	    }
	        	}
	  		    ans = max(ans, a[j][i]);
	        }
	    }
	    for (int j = 0; j < n; ++ j) p[j].first = -p[j].first;
	}
	cout << ans << endl;
	return 0;
}