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
   // k * y + k sticks so that trade k*y sticks to get k coal
   // 1 stick -> k*(y + 1) stick
   // min no of steps, 1 -> x,
   // 1 -> x -> 2x - 1 -> 3x - 2 -> 4x - 3 -> i*x - (i-1)
   // i steps i * x - (i - 1) sticks = k * (y + 1)
   // i * (x-1) = k * (y + 1) - 1

   long long x, y, k;
   cin >> x >> y >> k;
   long long num = k * (y + 1) - 1,
        den = x - 1;
   cout << (num + den - 1) / den + k << '\n';
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
