// Hack it and have it ;) //
/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows!* * * * * * */
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
   vector <int> ar(N);
   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
   }

   vector <int> me(N + 1), you(N + 1);

   // since we have fixed starting we need to work on suffixes
   // (better implementation choice)
   // me[i] -> min. no of skips points use to kill from i, i+1, ... N-1 if
   // ith boss was killed by me
   // you[i] -> min. no of skips points use to kill from i, i+1 ... N-1 if
   // ith boss was killed by you
   // final answer you[0]

   me[N] = you[N] = 0;
   for (int i = N-1; i >= 0; --i) {
      // calculate you[i]
      you[i] = me[i + 1] + ar[i];
      if (i + 2 <= N) {
         you[i] = min(you[i], me[i + 2] + ar[i] + ar[i + 1]);
      }
      // calc me[i]
      me[i] = you[i + 1];
      if (i + 2 <= N)  {
         me[i] = min(me[i], you[i + 2]);
      }
   }
   cout << you[0] << '\n';
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
