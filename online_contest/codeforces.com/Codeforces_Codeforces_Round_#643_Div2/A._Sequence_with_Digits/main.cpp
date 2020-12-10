#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

inline int get (long long x) {
  long long mn = 9, mx = 0;
  while (x)
    mn = min(mn, x % 10), mx = max(mx, x % 10), x /= 10;
  return mn * mx;
}

void solve() {
  long long a1, K;
  cin >> a1 >> K;

  long long res = a1;
  for (long long i = 0; i < K - 1; ++i) {
    res += get (res);
    if (get(res) == 0)
      break;
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
