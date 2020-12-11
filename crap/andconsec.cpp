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
   int N = rand() % 1000;
   if (N != 1 and N == (N & (-N))) {  // not one and power of two
      return;
   }
   cout << N << "\n";
   vector <int> pre = {2, 3, 1, 5 ,4};
   for (int i = 0; i < min(N, 5); ++i) {
      cout << pre[i] << ' ';
   }
   for (int i = 6; i <= N;) {
      if (i == (i & (-i))) { // this won't happen ever for i == N
         cout << i + 1 << ' ' << i << ' ';
         i += 2;
      }
      else {
         cout << i << ' ';
         i += 1;
      }
   }
   cout << endl;
   return;
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 100;
  // cin >> tc;
  cout << tc << '\n';

  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
