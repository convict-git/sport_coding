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
   vector <long long> fac(20);
   {
      fac[0] = 1;
      for (int i = 1; i < 20; ++i) {
         fac[i] = fac[i-1] * i;
      }
   }

   int N, K;
   long long S;
   cin >> N >> K >> S;
   vector <int> ar(N);
   {
      for (int i = 0; i < N; ++i) {
         cin >> ar[i];
      }
   }

   vector <int> N_val = { N / 2, N - N / 2 };
   vector<vector <int>> A(2, vector <int> ());
   {
      for (int i = 0; i < N; ++i) {
         if (i < N_val[0]) A[0].push_back(ar[i]);
         else A[1].push_back(ar[i]);
      }
   }

   vector <vector <map <long long, int>>> mp(2);
   {
      for (int rot = 0; rot < 2; ++rot) {
         mp[rot].assign(N + 1, map <long long, int> ());
         for (int mask = 0; mask < (1 << N_val[rot]); ++mask) {
            for (int sub_mask = mask; ; sub_mask = (sub_mask - 1) & mask) {
               int k_val = __builtin_popcount(sub_mask);
               bool ok = true;
               long long sm = 0;
               for (int i = 0; i < N_val[rot]; ++i) {
                  if ((1 << i) & mask) {
                     if ((1 << i) & sub_mask) {
                        if (A[rot][i] > 18) {
                           ok = false;
                           break;
                        }
                        else sm += fac[A[rot][i]];
                     }
                     else sm += A[rot][i];
                  }
               }
               if (ok) {
                  mp[rot][k_val][sm]++;
               }
               if (sub_mask == 0) break;
            }
         }
      }
   }

   long long res = 0;
   for (int i = 0; i <= K; ++i) {
      for (auto val : mp[0][i]) {
         for (int j = 0; j <= K - i; ++j) {
            if (mp[1][j].find(S - val.first) != mp[1][j].end()) {
               res += 1ll * val.second * mp[1][j][S - val.first];
            }
         }
      }
   }
   cout << res << '\n';
   return;
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
