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
   vector <int> L(3);
   vector <int> C(3);
   for (int i = 0; i < 3; ++i) cin >> L[i];
   for (int i = 0; i < 3; ++i) cin >> C[i];

   int N, A, B;
   cin >> N >> A >> B;

   if (A > B) swap(A, B);
   vector <long long> dist(N + 1);
   for (int i = 2; i <= N; ++i) {
      cin >> dist[i];
   }

   vector <long long> dp(N + 1, LLONG_MAX);
   dp[A] = 0;
   for (int i = A - 1; i <= B; ++i) {
      if (dp[i] != LLONG_MAX) {
         for (int rot = 0; rot < 3; ++rot){
            for (int j = i + 1; j <= B; ++j) {
               if (dist[j] - dist[i] <= L[rot]) {
                  dp[j] = min(dp[j], dp[i] + C[rot]);
               }
               else break;
            }
         }
      }
   }
   cout << dp[B] << '\n';
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
