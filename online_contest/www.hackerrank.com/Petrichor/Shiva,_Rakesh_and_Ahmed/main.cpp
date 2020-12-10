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
   vector <string> S =
   {"rakeshivahmed", "rakeshiva", "shivahmed", "ahmed", "rakesh", "shiva" };
   vector <int> cost {2, 1, 1, 1, 1, 1};
   int n;
   cin >> n;
   string inp;
   cin >> inp;
   int res = 0;
   for (int i = 0; i < n; ) {
      bool found = false;
      for (int j = 0; j < (int)S.size(); ++j) {
         string ss = S[j];
         if (n - 1 - i + 1 >= (int)ss.size()) {
            if (inp.substr(i, (int)ss.size()) == ss) {
               res += cost[j];
               i += (int)ss.size();
               found = true;
               break;
            }
         }
      }
      if (!found) ++i;
   }
   cout << res << "\n";
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
