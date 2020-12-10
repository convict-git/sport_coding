#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
#define ll long long
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

void solve() {
   ll N, M;
   cin >> N >> M;

   while (N != 0 and M != 0 and (N >= 2 * M or M >= 2 * N)) {
      int x = 1;
      while (M != 0 and N >= (1ll << x) * M) ++x;
      --x;
      if (x >= 1 and N >= (1ll << x) * M) {
         N -= (1ll << x) * M;
      }
      x = 1;
      while (N != 0 and M >= (1ll << x) * N) ++x;
      --x;
      if (x >= 1 and M >= (1ll << x) * N) {
         M -= (1ll << x) * N;
      }
   }
   cout << N << ' ' << M << '\n';
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
