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

template <class T>
T pwExp(T x, int y) {
   T res = 1;
   while (y) {
      if (y & 1) res *= x;
      x *= x;
      y >>= 1;
   }
   return res;
}

void solve()
{
   int N;
   double p;
   cin >> N >> p;

   double res = 1 + pwExp(-p*2 + 1, N);
   cout << res / 2 << '\n';
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
