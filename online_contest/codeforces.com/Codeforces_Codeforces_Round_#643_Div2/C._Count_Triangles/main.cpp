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

void solve() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;

  long long res = 0;

  vector <long long> f(d + 1);
  for (int s = c; s <= d; ++s) {
    int x = ceil((double) s / 2), y = floor((double) s / 2);
    debug(x, y);
    // x - k >= a && x - k <= b
    int kl = max(0, x - a), kr = max(0, x - b);
  }

  /* // slow solution O(n * n)
  vector <long long> lz(d + 1);
  for (int x = a; x <= b; ++x) {
    for (int y = b; y <= c; ++y) {
      if (x + y > c) {
        lz[c]++;
        if (x + y <= d) lz[x + y]--;
      }
    }
  }

  for (int i = c + 1; i <= d; ++i)
    lz[i] += lz[i - 1];

  for (int z = c; z <= d; ++z)
    res += lz[z];
    */
  cout << res << '\n';
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
