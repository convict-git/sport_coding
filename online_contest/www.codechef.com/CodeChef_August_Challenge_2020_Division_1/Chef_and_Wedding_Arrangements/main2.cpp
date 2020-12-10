#include      <bits/stdc++.h>
using namespace std;

const int Maxn = 1e3 + 10;
int n, k;
int dp[Maxn], f[Maxn], pref[110][Maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie (nullptr);
  cout.precision (10); cout << fixed;
  int tc; cin >> tc;
  while (tc--) {
     cin >> n >> k;
     int fm = 0;
     memset(f, 0, sizeof(f));
     for (int i = 1; i <= n; ++i) {
        cin >> f[i];
        fm = max(fm, f[i]);
        dp[i] = INT_MAX;
     }

     for (int fval = 0; fval <= fm; ++fval) {
        for (int i = 1; i <= n; ++i) {
           pref[fval][i] = pref[fval][i - 1] + (fval == f[i]);
        }
     }

     dp[0] = 0;
     for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
           int cost = 0;
           for (int fval = 0; fval <= fm; ++fval) {
              int subcost = pref[fval][i] - pref[fval][j];
              if (subcost > 1) cost += subcost;
           }
           dp[i] = min(dp[i], dp[j] + k + cost);
        }
     }

     cout << dp[n] << '\n';
  }
  return 0;
}
