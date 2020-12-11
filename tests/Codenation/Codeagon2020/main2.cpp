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

void preproc()
{
}

void solve()
{
   int N = 10;
   vector <int> pi(N);
   iota(pi.begin(), pi.end(), 1); // 1...N

   vector <vector <int>> vt(N + 1, vector <int> ());
   do {
      int res = 0;
      for (int i = 0; i < N; ++i) {
         bool good = true;
         for (int j = 0; j < i; ++j) {
            if (pi[j] > pi[i]) {
               good = false;
               break;
            }
         }
         if (good) ++res;
      }
      if (vt[res].empty()) {
         for (int i = 0; i < N; ++i){
            vt[res].push_back( pi[i]);
         }
      }
   } while (next_permutation(pi.begin(), pi.end())); // lexi increase

   for (int val = 1; val <= N; ++val) {
      debug(val, vt[val]);
   }
}

signed main()
{
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
