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
   string s;
   cin >> s;

   int costMin = N;

   for (int i = 0; i < N; ++i) {
      if (2 * i + 1 <= N - 1) {
         if (s.substr(0, i + 1) == s.substr(i + 1, i + 1)) {
            costMin = min(costMin, i + 1 + 1 + N - 1 - (2 * i + 2) + 1);
         }
      }
   }
   cout << costMin << '\n';
   return;
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
