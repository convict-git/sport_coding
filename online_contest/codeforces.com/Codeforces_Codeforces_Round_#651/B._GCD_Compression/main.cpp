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
   vector <pair <int ,int>> even;
   vector <pair <int ,int>> odd;
   for (int i = 0; i < 2 * n; ++i) {
      int ai; cin >> ai;
      if (ai & 1) odd.push_back({ai, i+1});
      else even.push_back({ai, i+1});
   }

   int osz = (int)odd.size(), esz = (int)even.size();

   if (osz % 2 == 0) {
      if (osz == 0) {
         even.pop_back();
         even.pop_back();
      }
      else {
         odd.pop_back();
         odd.pop_back();
      }
   }
   else {
      odd.pop_back();
      even.pop_back();
   }

   while (!odd.empty()) {
      cout << odd.back().second << ' ';
      odd.pop_back();
      cout << odd.back().second << '\n';
      odd.pop_back();
   }
   while (!even.empty()) {
      cout << even.back().second << ' ';
      even.pop_back();
      cout << even.back().second << '\n';
      even.pop_back();
   }
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
