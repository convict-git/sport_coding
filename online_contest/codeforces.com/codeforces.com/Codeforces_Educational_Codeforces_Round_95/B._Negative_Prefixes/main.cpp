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
   vector <int> fixed(N);
   vector <int> value;
   for (int i = 0; i < N; ++i) {
      cin >> fixed[i];
      if (fixed[i] == 0) {
         value.push_back(ar[i]);
      }
   }
   sort(value.begin(), value.end(), greater <int> ());
   for (int i = 0, j = 0; i < N; ++i) {
      if (fixed[i] == 0) {
         ar[i] = value[j];
         ++j;
      }
      cout << ar[i] << " \n"[i == N - 1];
   }
   return;
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