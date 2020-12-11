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

/* Selection Sorting:
 * worse case O(N * N) but does only N swaps (write) which
 * can be essential in some systems like flash drive where writes are
 * quite costlier.
 */
void solve()
{
   int N;
   cin >> N;
   vector <int> Ar(N);
   for (int &a : Ar) cin >> a;

   for (int curIdx = 0; curIdx < N; ++curIdx) {
      pair <int, int> mnVal = {INT_MAX, -1};
      for (int i = curIdx; i < N; ++i) {
         mnVal = min(mnVal, {Ar[i], i});
      }
      swap(Ar[curIdx], Ar[mnVal.second]);
   }

   for (int &a : Ar) cout << a << ' ';
   cout << '\n';
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
