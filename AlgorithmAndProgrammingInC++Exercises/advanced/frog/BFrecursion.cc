#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;

const int N = 1005;
pair<int, int> a[N][N];
int ans, n;
pii p[N];

void upTri(int i, int j, int delta) {
    for (int k = j + 1; k < n; ++k) {
        if (p[k].first - p[j].first >= delta) {
            if (a[i][j].first + p[k].second < a[j][k].first 
                && p[k].first - p[j].first > a[j][k].second)
                return;
            a[j][k] = make_pair(a[i][j].first + p[k].second, 
                                p[k].first - p[j].first);
            ans = max(ans, a[j][k].first);
            int dist = p[k].first - p[j].first;
            upTri(j, k, dist);
        }
    }
}
 
void loTri(int i, int j, int delta) {
    for (int k = j - 1; k >= 0; --k) {
        if (p[j].first - p[k].first >= delta) {
            if (a[i][j].first + p[k].second < a[j][k].first
                && p[j].first - p[k].first > a[j][k].second)
                return;
            a[j][k] = make_pair(a[i][j].first + p[k].second,
                                p[j].first - p[k].first);
            ans = max(ans, a[j][k].first);
            int dist = p[j].first - p[k].first;
            loTri(j, k, dist);
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, s;
        cin >> x >> s;
        p[i] = make_pair(x,s);
    }
    sort(p, p + n);
    for (int i = 0; i < n; ++i) {
    	a[i][i] = make_pair(p[i].second, 0);
    	ans = max(ans, a[i][i].first);
    }
    
    for (int i = 0; i < n; ++i) {
    	for (int j = i + 1; j < n; ++j) {
            a[i][j] = make_pair(p[i].second + p[j].second, p[j].first - p[i].first);
            ans = max(ans, a[i][j].first);
            upTri(i, j, p[j].first - p[i].first);
        }
    }

    for (int i = n - 1; i >= 0; --i) {
    	for (int j = i - 1; j >= 0; --j) {
            a[i][j] = make_pair(p[i].second + p[j].second, p[i].first - p[j].first);
            ans = max(ans, a[i][j].first);
            loTri(i, j, p[i].first - p[j].first);
        }
    }

    cout << ans << endl;
    return 0;
}
