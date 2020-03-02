#include      <bits/stdc++.h>
using namespace std;

signed main() {
  const int D = 21;
  int n;
  cin >> n;
  vector <int> ar(n);
  for (int i = 0; i < n; ++i) {
    cin >> ar[i];
  }

  vector <vector <int>> dp(n, vector <int> (D));
  for (int i = 0; i < n; ++i)  {
    cin >> ar[i];
    dp[i][0] = ar[i];
  }

  for (int d = 1; d < D; ++d) {
    for (int i = 0; i < n; ++i) {
      if (i + (1 << d) - 1 <= n - 1) {
        dp[i][d] = max(dp[i][d-1], dp[i + (1 << (d-1))][d-1]);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    int cur = i;
    for (int d = D-1; d >= 0; --d) {
      if (cur + (1 << d) - 1 <= n - 1 && dp[cur][d] <= ar[i]) {
        cur += (1 << d);
      }
    }
    cout << cur << '\n';
  }

  return EXIT_SUCCESS;
}


