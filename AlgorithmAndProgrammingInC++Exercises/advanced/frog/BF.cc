#include <iostream>
#include <utility>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

typedef pair<int, int> pii;
map<string, int> dp;
const int N = 1005;
int ans, n;
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
        dp[to_string(i).append(to_string(i)).append(to_string(0))] = p[i].second;
        dp[to_string(i).append(to_string(i+1)).append(to_string(p[i+1].first-p[i].first))] = p[i].second + p[i+1].second;
        dp[to_string(i+1).append(to_string(i)).append(to_string(p[i+1].first-p[i].first))] = p[i].second + p[i+1].second;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 2; j < n; ++j) {
            for (int k = i + 1; k < j; ++ k) {
                int dist = p[j].first - p[k].first;
                int step = k - 1;
                int d = p[k].first - p[step].first;;
                while (d <= dist && step >= i) {
                    dp[to_string(i).append(to_string(j)).append(to_string(dist))] = 
                    max(dp[to_string(i).append(to_string(k)).append(to_string(d))] + p[j].second, 
                        dp[to_string(i).append(to_string(j)).append(to_string(dist))]);
                    ans = max(ans, dp[to_string(i).append(to_string(j)).append(to_string(dist))]);
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
                    dp[to_string(j).append(to_string(i)).append(to_string(dist))] = 
                    max(dp[to_string(j).append(to_string(k)).append(to_string(d))] + p[i].second, 
                        dp[to_string(j).append(to_string(i)).append(to_string(dist))]);
                    ans = max(ans, dp[to_string(j).append(to_string(i)).append(to_string(dist))]);
                    ++ step;
                    d = p[step].first - p[k].first;
                }
            }
        }
    }
    
            


    cout << ans << endl;
    return 0;
}
