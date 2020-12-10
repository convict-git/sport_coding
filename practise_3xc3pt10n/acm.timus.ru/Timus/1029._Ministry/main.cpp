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

using pp = pair <long long, pair <int, int>>; // value, flr, room

int M, N;
void preproc()
{
}

void solve()
{
   vector <vector <int>> cost(M, vector <int> (N));
   for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
         cin >> cost[i][j];
      }
   }

   vector <vector <pair <int, int>>> pi(M, vector <pair <int, int>>(N));

   priority_queue <pp, vector <pp>, greater <pp>> pq;
   vector <vector <bool>> vis(M, vector <bool> (N));
   vector <vector <long long>> dp(M, vector <long long> (N, LLONG_MAX));
   for (int r = 0; r < N; ++r) {
      pq.push({cost[M - 1][r], {M - 1, r}});
      dp[M - 1][r] = cost[M - 1][r];
      pi[M - 1][r] = {0, 0};
   }

   auto is_valid = [&] (int f, int r) -> bool {
      return f >= 0 and r >= 0 and f < M and r < N and !vis[f][r];
   };

   int dx[] = {-1, 0, 0};
   int dy[] = {0, -1, 1};

   while (!pq.empty()) {
      pp frnt = pq.top();
      long long val = frnt.first;
      int flr = frnt.second.first;
      int room = frnt.second.second;
      pq.pop();

      if (vis[flr][room]) {
         continue;
      }
      vis[flr][room] = true;

      for (int rot = 0; rot < 3; ++rot) {
         int n_flr = flr + dx[rot];
         int n_room = room + dy[rot];

         long long &dp_val = dp[n_flr][n_room];

         if (is_valid(n_flr, n_room) and
               dp_val > val + cost[n_flr][n_room]) {
            dp_val = val + cost[n_flr][n_room];
            pi[n_flr][n_room] = {-1 * dx[rot], -1 * dy[rot]};
            pq.push({dp_val, {n_flr, n_room}});
         }
      }
   }

   int last_room = (int) (min_element(dp[0].begin(), dp[0].end()) - dp[0].begin());
   int flr = 0;

   vector <int> v;
   v.push_back(last_room + 1);
   while (pi[flr][last_room] != make_pair(0, 0)) {
      auto p = pi[flr][last_room];
      flr += p.first;
      last_room += p.second;
      v.push_back(last_room + 1);
   }

   int _sz = (int)v.size();
   for (int i = 0; i < _sz; ++i) {
      cout << v[i] << " \n"[i == _sz - 1];
   }
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
     while (cin >> M >> N)  {
        solve();
     }
  }
  return EXIT_SUCCESS;
}
