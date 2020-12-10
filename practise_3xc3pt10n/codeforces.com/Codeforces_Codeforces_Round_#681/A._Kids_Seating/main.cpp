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
   int N;
   cin >> N;
   vector <int> used(4 * N + 1);
   vector <int> res;

   for (int i = 4*N; i >= 1; i -= 2) {
      if (!used[i]) {
         res.push_back(i);
         for (int j = 2; i / j > 0; ++j) {
            used[i / j] = true;
         }
      }
   }

   for (int i = 0; i < N; ++i) {
      cout << res[i] << " \n"[i == N - 1];
   }
}

signed main()
{
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

