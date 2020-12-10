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

const int Mxn = 2e5 + 10;
int N, Q;
int h[Mxn], a[Mxn];

void preproc() {
}

void solve() {
   // q * sqrt(N) will also pass most probably
   cin >> N >> Q;
   for (int i = 0; i < N; ++i) {
      cin >> h[i];
   }
   for (int i = 0; i < N; ++i) {
      cin >> a[i];
   }

   // since the order matters, process them online
   while (Q--) {
      int type, b, k, c;
      cin >> type;
      if (type == 1) {
         cin >> b >> k;
      }
      else  {
         cin >> b >> c;
      }
   }
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
