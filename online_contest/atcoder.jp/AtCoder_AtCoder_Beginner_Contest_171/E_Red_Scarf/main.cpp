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
   int N;
   cin >> N;
   vector <int> ar(N);
   vector <int> pref(N), suff(N);
   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
      pref[i] = (i ? pref[i - 1] : 0) ^ ar[i];
   }
   for (int i = N-1; i >= 0; --i) {
      suff[i] = (i == N-1 ? 0 : suff[i+1]) ^ ar[i];
   }

   for (int i = 0; i < N; ++i) {
      ar[i] = (i ? pref[i-1] : 0) ^ (i == N-1 ? 0 : suff[i+1]);
      cout << ar[i] << " \n"[i == N-1];
   }
   int Q;
   cin >> Q;
   while (Q--) {
      int L, R;
      cin >> L >> R; --L, --R;
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
