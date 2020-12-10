#include <array>
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
//
const int Maxn = 2e5 + 10;
int ar[Maxn];
int N, K;

void preproc()
{
}

void solve()
{
   std::array <int, Maxn> Ar;
   cin >> N >> K;
   vector <int> st;
   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
   }
   sort(ar, ar + N, greater <int> ());

   int sumTillK = 0;
   for (int i= 0; i < K; ++i) {
      sumTillK += ar[i];
   }
   cout << sumTillK << '\n';
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
