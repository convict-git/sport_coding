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

const int Maxn = 510;
int dp[Maxn][Maxn], cost[Maxn][Maxn];
int cnt[Maxn];
int N, M, K;
vector <int> dProfile[Maxn];

void preproc() {
}

void solve() {
   cin >> N >> M >> K;
   int mnClass = 0;

   for (int d = 0; d < N; ++d) {
      string s;
      cin >> s;
      dProfile[d].clear();
      cnt[d] = 0;
      for (int i = 0; i < (int)s.size(); ++i) {
         if (s[i] == '1') {
            dProfile[d].push_back(i);
            ++cnt[d];
         }
      }
      mnClass += cnt[d];
   }
   mnClass = max(0, mnClass - K);
   if (mnClass == 0) {
      cout << 0 << '\n';
      return;
   }

   for (int d = 0; d < N; ++d) { // O (N ^ 3)
      for (int k = 0; k <= K; ++k) {
         dp[d][k] = cost[d][k] = INT_MAX;
      }

      int sz = (int)dProfile[d].size();

      cost[d][cnt[d]] = 0;
      for (int st = 0; st < sz; ++st) {
         for (int en = st; en < sz; ++en) {
            int timeSpent = dProfile[d][en] - dProfile[d][st] + 1;
            int classTaken = en - st + 1;
            int classLeft = cnt[d] - classTaken;
            cost[d][classLeft] = min(cost[d][classLeft], timeSpent);
         }
      }
   }

   for (int k = 0; k <= K; ++k) {
      dp[0][k] = cost[0][k];
   }
   for (int d = 1; d < N; ++d) {
      for (int k = 0; k <= K; ++k) {
         for (int x = 0; x <= k; ++x) {
            if (dp[d - 1][k - x] != INT_MAX and cost[d][x] != INT_MAX) {
               dp[d][k] = min(dp[d][k], dp[d - 1][k - x] + cost[d][x]);
            }
         }
      }
   }

   int res = INT_MAX;
   for (int k = 0; k <= K; ++k) {
      res = min(res, dp[N - 1][k]);
   }
   cout << res << '\n';
}


signed main() {
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
