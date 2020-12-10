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
   /// you have atmost 20 queries and log2(1e6) <= 20
   // so queury for each bit it seems
   int N;
   cin >> N;

   const int Logn = 20;

   int res = 0;

   for (int i = 0; i < Logn; ++i) {
      int query = (1 << i);
      cout << 1 << ' ' <<  query << '\n';
      cout << flush;
      int curRes;
      cin >> curRes;

      curRes /= (1 << i);

      if (curRes & 1) { // odd occurance
         res |= (1 << i);
      }
   }
   cout << 2 << ' ' << res <<  '\n';
   cout << flush;
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
