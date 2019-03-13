#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;

const int N = 1005;
int a[N][N][1000000 + 5], ans, n;
pii p[N];


int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, s;
        cin >> x >> s;
        p[i] = make_pair(x,s);
    }
    sort(p, p + n);
    for (int i = 0; i < n; ++i) {
        a[i][i][0] = p[i].second;
        a[i][i+1][p[i+1].first-p[i].first] = p[i].second + p[i+1].second;
        if (i < n - 1) a[i+1][i][p[i+1].first-p[i].first] = p[i].second + p[i+1].second;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 2; j < n; ++j) {
            for (int k = i + 1; k < j; ++ k) {
                int dist = p[j].first - p[k].first;
                int step = k - 1;
                int d = p[k].first - p[step].first;;
                while (d <= dist && step >= i) {
                    a[i][j][dist] = max(a[i][k][d] + p[j].second, a[i][j][dist]);
                    ans = max(ans, a[i][j][dist]);
                    -- step;
                    d = p[k].first - p[step].first;
                }
            }
        }
    }

    for (int j = n - 1; j >= 0; --j) {
        for (int i = j - 2; i >= 0; --i) {
            for (int k = j - 1; k > i; -- k) {
                int dist = p[k].first - p[i].first;
                int step = k + 1;
                int d = p[step].first - p[k].first;;
                while (d <= dist && step <= j) {
                    a[j][i][dist] = max(a[j][k][d] + p[i].second, a[j][i][dist]);
                    ans = max(ans, a[j][i][dist]);
                    ++ step;
                    d = p[step].first - p[k].first;
                }
            }
        }
    }
    
            


    cout << ans << endl;
    return 0;
}
