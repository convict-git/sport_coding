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
   bool is_same = true;
   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
      if (i and ((ar[i] & 1) ^ (ar[i - 1] & 1)) == 1) {
         is_same = false;
      }
   }
   if (!is_same) {
      sort(ar.begin(), ar.end());
   }
   for (int i = 0; i < N; ++i) {
      cout << ar[i] << " \n"[i == N - 1];
   }
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
