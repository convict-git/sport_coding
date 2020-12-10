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
   int n;
   cin >> n;

   vector <pair <int, int>> store;
   int x=0, y=0;
   ++n;
   store.push_back({x, y});
   while (n--) {
      store.push_back({x+1, y});
      store.push_back({x, y+1});
      store.push_back({x+1, y+1});
      x += 1, y += 1;
   }
   cout << store.size() << '\n';
   for (auto s : store) {
      cout << s.first << ' ' << s.second << '\n';
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
