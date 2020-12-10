#include <bits/stdc++.h>
using namespace std;

const int N = 101;
int dp[N][N * N];
int ass[N];
int n, k, ar[N];

signed main() {
  memset(dp, 0, sizeof(dp));
  memset(ass, 0, sizeof(ass));
  cin >> k;

  int sm = 0;
  n = 0;
  for (int i = 1; i <= k; ++i)
    cin >> ar[i], sm += ar[i], n = max(ar[i], n);

  dp[0][0] = 1;

  for (int i = 1; i <= k; ++i) {
    for (int j = 0; j <= n * k; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j - ar[i] >= 0) dp[i][j] |= dp[i - 1][j - ar[i]];
    }
  }

  if (sm % 2 == 0 && dp[k][sm / 2]) {
    cout << "YES\n";
    int idx = k, curwt = sm / 2;
    while (idx > 0) {
      if (curwt - ar[idx] >= 0 && dp[idx - 1][curwt - ar[idx]]) {
        ass[idx] = 1;
        curwt -= ar[idx];
      }
      else ass[idx] = -1;
      --idx;
    }
    for (int i = 1; i <= k; ++i) {
      cout << ass[i] * ar[i] << " \n"[i == k];
    }
  }
  else cout << "NO\n";

  return EXIT_SUCCESS;
}


