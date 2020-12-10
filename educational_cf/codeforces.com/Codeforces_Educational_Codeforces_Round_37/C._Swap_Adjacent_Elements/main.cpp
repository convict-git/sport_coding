#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you Find it right. Practice until you can’t Find it wrong

void preproc() {
}

vector <int> rep;
inline int Find (int x) {
   return x == rep[x] ? x : rep[x] = Find(rep[x]);
}

void solve() {
   int n;
   cin >> n;
   vector <int> ar(n);
   vector <pair <int, int>> pos;
   string s;
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
      pos.push_back(make_pair(ar[i], i));
   }
   sort(pos.begin(), pos.end());
   cin >> s;
   rep.assign(n, 0);
   iota(rep.begin(), rep.end(), 0);
   for (int i = 0; i < n-1; ++i) {
      if (s[i] == '1') {
         int rp = rep[i], rn = rep[i+1];
         rep[rp] = rn;
      }
   }
   for (int i = 0; i < n; ++i) {
      int cur = pos[i].second;
      if (Find(cur) != Find(i)) {
         cout << "NO\n";
         return;
      }
   }
   cout << "YES\n";
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
