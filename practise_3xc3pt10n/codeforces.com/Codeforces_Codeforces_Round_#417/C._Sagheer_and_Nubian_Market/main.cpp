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
   // if he buys k items
   // xj + aj/k
   int N, S;
   cin >> N >> S;

   vector <pair <int, int>> Ar(N);
   for (int i = 0; i < N; ++i) {
      cin >> Ar[i].second;
      Ar[i].first = i + 1;
   }

   auto check = [&] (int Kval) -> long long {
      sort(Ar.begin(), Ar.end(),
            [&] (auto p, auto q) -> bool {
            return 1ll * Kval * p.first + p.second
            < 1ll * Kval * q.first + q.second;
            }
            );

      long long res = 0;
      for (int i = 0; i < Kval; ++i) {
         res += 1ll*Kval*Ar[i].first + Ar[i].second;
      }
      return res;
   };

   int low = 0, high = N;
   while (low <= high) {
      int guess = (low + high) / 2;
      if (check(guess) <= S) {
         low = guess + 1;
      }
      else high = guess - 1;
   }

   cout << high << ' ' <<  check(high) << '\n';

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
