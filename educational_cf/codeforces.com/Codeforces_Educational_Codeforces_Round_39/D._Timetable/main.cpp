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
int N, M, K;
vector <int> dProfile[Maxn];

void preproc() {
}

void solve() {
   cin >> N >> M >> K;
   int mnClass = 0;
   vector <int> v;

   for (int d = 0; d < N; ++d) {
      string s;
      cin >> s;
      dProfile[d].clear();
      for (int i = 0; i < (int)s.size(); ++i) {
         if (s[i] == '1') {
            dProfile[d].push_back(i);
            ++mnClass;
         }
      }
   }

   mnClass = max(0, mnClass - K);
   if (mnClass == 0) {
      cout << 0 << '\n';
      return;
   }
   // preproces to get cost[i][k]
   // ith d of the week, if atleast k classes are taken, what's the min hours spent


   for (int d = 0; d < N; ++d) { // O (N ^ 3)
      for (int k = 0; k <= mnClass; ++k) {
         dp[d][k] = cost[d][k] = INT_MAX;
      }

      int sz = (int)dProfile[d].size();

      cost[d][0] = 0;
      for (int st = 0; st < sz; ++st) {
         for (int en = st; en < sz; ++en) {
            int timeSpent = dProfile[d][en] - dProfile[d][st] + 1;
            int classTaken = en - st + 1;
            cost[d][classTaken] = min(cost[d][classTaken], timeSpent);
         }
      }

      // normalize for the def atleast
      for (int k = mnClass - 1; k >= 0; --k) {
         cost[d][k] = min(cost[d][k], cost[d][k + 1]);
      }
   }

   // calculate dp[d][k]
   // if till dth day, atleast k classes are taken, what's the min hours spent
   for (int k = 0; k <= mnClass; ++k) {
      dp[0][k] = cost[0][k];
   }

   for (int d = 1; d < N; ++d) {
      for (int k = 0; k <= mnClass; ++k) {
         for (int x = 0; x <= k; ++x) {
            if (dp[d - 1][k - x] != INT_MAX and cost[d][x] != INT_MAX) {
               dp[d][k] = min(dp[d][k], dp[d - 1][k - x] + cost[d][x]);
            }
         }
      }
   }
   cout << dp[N - 1][mnClass] << '\n';
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
