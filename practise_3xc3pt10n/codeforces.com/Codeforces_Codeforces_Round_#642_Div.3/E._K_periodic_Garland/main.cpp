#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.cpp"
#else
#define debug(x...) 42
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  int ones = 0;
  vector <int> ocl(n);

  for (int i = n - 1; i >= 0; --i) {
    ones += s[i] == '1';
    ocl[i] = (i + k < n ? ocl[i + k] : 0) + (s[i] == '1');
  }

  int res = INT_MAX;
  for (int i = 0; i < k; ++i) {
    int sz = (n - i) / k + ((n - i) % k != 0);
    vector <int> zdp(sz), odp(sz);
    int down = ones - ocl[i];

    for (int j = 0; j < sz; ++j) {
      int idx = i + j * k;
      zdp[j] = (j ? zdp[j - 1] : 0) + (s[idx] != '0');
      odp[j] = (j ? min(odp[j - 1], zdp[j - 1]) : 0) + (s[idx] != '1');

      res = min({
          res,
          odp[j] + down + (idx + k < n ? ocl[idx + k] : 0),
          zdp[j] + down + ocl[idx]
          });
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

