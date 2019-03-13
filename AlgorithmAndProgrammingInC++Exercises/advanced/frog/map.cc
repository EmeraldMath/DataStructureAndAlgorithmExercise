#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
const int N = 1e3+5;
int dp[N][N], ans;
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
    for (int i = 1; i <= n; ++ i) ans = max(ans, dp[i][i] = p[i].second);
    //for (int j = 2; j <= n; ++ j) dp[1][j] = dp[1][j - 1] + p[j].second;
    //for (int j = n - 1; j > 0; -- j) dp[n][j] = dp[n][j + 1] + p[j].second;

    for (int i = 1; i < n; ++ i)
    	for (int j = i + 1; j <= n; ++ j)
    		for (int k = i; k < j; ++ k)
    		    if (p[j].first - p[k].first >= p[k].first - p[i].first) {
    		        dp[i][j] = max(dp[i][k] + p[j].second, dp[i][j]);
                    ans = max(ans, dp[i][j]);
    		    }

    for (int i = n; i > 1 ; -- i)
    	for (int j = i - 1; j > 0; -- j)
    		for (int k = i; k > j; -- k)
    			if (p[k].first - p[j].first >= p[i].first - p[k].first) {
    				dp[i][j] = max(dp[i][k] + p[j].second, dp[i][j]);
    				ans = max(ans, dp[i][j]);
    			}

    cout << ans << endl;
    return 0;
}