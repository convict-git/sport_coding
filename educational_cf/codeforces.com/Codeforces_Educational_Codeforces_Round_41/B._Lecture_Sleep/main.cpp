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
   int N, K;
   cin >> N >> K;
   vector <int> ar(N);
   vector <int> awake(N);
   int sm = 0;

   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
   }
   for (int i = 0; i < N; ++i) {
      cin >> awake[i];
      if (awake[i]) {
         sm += ar[i];
         ar[i] = 0;
      }
   }

   int mx = 0;
   for (int i = 0; i < min(K, N); ++i){
      mx += ar[i];
   }

   int cur = mx;
   for (int i = K; i < N; ++i) {
      cur -= ar[i - K];
      cur += ar[i];
      mx = max(mx, cur);
   }
   cout << sm + mx << '\n';
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
