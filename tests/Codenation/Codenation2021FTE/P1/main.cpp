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

typedef long long ll;

void preproc()
{
}

ll fn (ll x)
{
   ll res = (x * (x + 1) * (x * 2 + 1)) / 6;
   res += (x * (x + 1)) / 2;
   return res / 2;
}

void solve()
{
   ll N;
   cin >> N;

   ll low, L = 0, H = 1e5;

   while (L <= H) {
      ll X = (L + H) / 2;
      if (fn(X) > N) {
         H = X - 1;
      }
      else L = X + 1;
   }
   low = H;

   ll res = (low * (low + 1)) / 2;
   ll had = fn(low);

   if (had == N) { // perfect fit
      cout << res << '\n';
   }
   else { // not
      if (had + low + 1 >= N) {
         cout << res + N - had << '\n';
      }
      else {
         cout << res + low + 1 << '\n';
      }
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
