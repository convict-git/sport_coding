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
   // 2 3 1 5 4
   // 10 11 1 101 100 110
   int N;
   cin >> N;
   vector <int> ar(N);
   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
   }
   for (int i = 0; i < N - 1; ++i)  {
      if ((ar[i] & ar[i + 1]) == 0) {
         debug(ar[i], ar[i + 1]);
         cout << "Error\n";
         return;
      }
   }
   // cout << "good enough\n";
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
