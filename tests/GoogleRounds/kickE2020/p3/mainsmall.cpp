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

void solve()
{
   int N;
   cin >> N;
   struct Toy { int E, R; };
   vector <Toy> store(N);

   ll cyclesSum = 0;
   for (int i = 0; i < N; ++i) {
      cin >> store[i].E >> store[i].R;
      cyclesSum += store[i].E;
   }

   ll res = 0, resTotalE = cyclesSum;
   int resRem = 0;

   for (int mask = 1; mask < (1 << N); ++mask) {
      ll totalE = 0, curRes = 0;
      for (int i = 0; i < N; ++i) {
         if (mask & (1 << i)) {
            totalE += store[i].E;
         }
      }

      int curRem = N - __builtin_popcount(mask);
      for (int i = 0; i < N; ++i) {
         if (mask & (1 << i)) {
            if (totalE - store[i].E >= store[i].R) {
               curRes += store[i].E;
            }
            else {
               break;
            }
         }
      }
      if (curRes == totalE) {
         res = LLONG_MAX;
         resRem = curRem;
         resTotalE = 0;
         break;
      }

      if (res < curRes) {
         res = curRes;
         resRem = curRem;
         resTotalE = totalE;
      }
   }

   if (res == LLONG_MAX) {
      cout << resRem << ' ' << "INDEFINITELY\n";
   }
   else {
      cout << resRem << ' ' << res + resTotalE << '\n';
   }
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
