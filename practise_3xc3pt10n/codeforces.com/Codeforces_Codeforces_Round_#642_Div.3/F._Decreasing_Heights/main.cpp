#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.cpp"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

void solve() {
  int n, m;
  vector <vector <long long>> ar;

  cin >> n >> m;
  ar.assign(n, vector <long long> (m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> ar[i][j];
    }
  }

  long long res = LLONG_MAX;
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y) {
      long long start = ar[x][y] - x - y;
      vector <vector <long long>> dp;
      dp.assign(n, vector <long long> (m, LLONG_MAX));
      long long up, left;

      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          up = (i ? dp[i - 1][j] : LLONG_MAX);
          left = (j ? dp[i][j - 1] : LLONG_MAX);
          long long val = start + i + j;
          if (ar[i][j] < val) {
            continue;
          }

          if (!(up == LLONG_MAX && left == LLONG_MAX) || !(i | j)) {
            dp[i][j] = ar[i][j] - val + (i | j ? min(up, left) : 0ll);
          }
        }
      }
      res = min(res, dp[n - 1][m - 1]);
    }
  }

  cout << res << '\n';
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
