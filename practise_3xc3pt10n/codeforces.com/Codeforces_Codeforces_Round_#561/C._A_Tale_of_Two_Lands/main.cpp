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
   vector <long long> Ar(N);

   for (auto &a : Ar) { cin >> a; a = abs(a); }
   sort(Ar.begin(), Ar.end());

   long long res = 0;
   for (int i = 0; i < N; ++i) {
      // find the lowest element greater than equal to Ar[i]/2
      int itLow = int(lower_bound(Ar.begin(), Ar.end(),
               Ar[i] % 2 == 0 ? Ar[i]/ 2 : Ar[i]/2 + 1)
            - Ar.begin());;
      // find the highest element less than equal to 2 * Ar[i]/2
      int itHigh = int(upper_bound(Ar.begin(), Ar.end(), 2ll * Ar[i])
            - Ar.begin()) - 1;

      int numOfElements = itHigh - itLow;
      res += numOfElements;
   }
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
