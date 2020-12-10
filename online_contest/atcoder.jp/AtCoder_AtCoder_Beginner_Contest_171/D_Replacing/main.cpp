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
   map <int, int> mp;
   long long sm = 0;
   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
      ++mp[ar[i]];
      sm += ar[i];
   }

   int Q;
   cin >> Q;
   while (Q--) {
      int B, C;
      cin >> B >> C;
      int occ = mp[B];
      sm += 1ll*occ*(C - B);
      mp[B] = 0;
      mp[C] += occ;
      cout << sm << '\n';
   }
   return;
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
