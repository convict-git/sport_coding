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

void preproc() {
}

void solve() {
   int n, m;
   cin >> n >> m;
   struct point { int x = -1, y = -1; };
   point S, T;
   vector <string> mat(n);
   vector <point> spots;
   vector <int> dx {0, 0, -1, 1};
   vector <int> dy {1, -1, 0, 0};
   for (int i = 0; i < n; ++i) {
      cin >> mat[i];
      for (int j = 0; j < m; ++j) {
         if (mat[i][j] == 'S')
            S.x = i, S.y = j, mat[i][j] = '.';
         else if (mat[i][j] == 'T')
            T.x = i, T.y = j, mat[i][j] = '.';
         else if (mat[i][j] == '*')
            spots.push_back({i, j});
      }
   }
   const int inf = 1e9;
   vector <vector <int>> time;
   time.assign(n, vector <int> (m, inf));
   vector <vector <bool>> vis;
   vis.assign(n, vector <bool> (m));
   queue <point> q;
   auto ok = [&] (int x, int y) -> bool { // well to go
      return x < n && x >= 0 && y < m && y >= 0 && mat[x][y] == '.' && !vis[x][y];
   };
   for (auto el : spots) {
      q.push(el);
      time[el.x][el.y] = 0;
   }
   while (!q.empty()) {
      point p = q.front();
      q.pop();
      if (vis[p.x][p.y])
         continue;
      vis[p.x][p.y] = true;
      for (int rot = 0; rot < 4; ++rot) {
         int cx = p.x + dx[rot];
         int cy = p.y + dy[rot];
         if (ok(cx, cy)) {
            q.push({cx, cy});
            time[cx][cy] = time[p.x][p.y] + 1;
         }
      }
   }
   vector <vector <int>> cur_time;
   vector <vector <point>> pi;
   cur_time.assign(n, vector <int> (m));
   pi.assign(n, vector <point> (m));
   vis.assign(n, vector <bool> (m));
   q.push({S.x, S.y}); // initialize for start
   cur_time[S.x][S.y] = 0;
   while (!q.empty()) { // do bfs to with the cur time
      point p = q.front();
      q.pop();
      if (vis[p.x][p.y])
         continue;
      vis[p.x][p.y] = true;
      int t = cur_time[p.x][p.y]; // cur time in bfs
      for (int rot = 0; rot < 4; ++rot) {
         int cx = p.x + dx[rot];
         int cy = p.y + dy[rot];
         if (ok(cx, cy) && t + 1 < time[cx][cy]) { // if time is less than virus' arrival
            q.push({cx, cy});
            cur_time[cx][cy] = t + 1; // upd the cur time + time taken to move
            pi[cx][cy] = {p.x, p.y};
         }
      }
   }
   bool found = false;
   for (int rot = 0; rot < 4; ++rot) { // any of the neigh of T is vis
      int cx = T.x + dx[rot];
      int cy = T.y + dy[rot];
      if (ok(cx, cy)) {
         found = true;
         vector <point> res;
         res.push_back({T.x, T.y});
         res.push_back({cx, cy});
         while (!(cx == S.x && cy == S.y)) {
            point bk = pi[cx][cy];
            cx = bk.x, cy = bk.y;
            res.push_back({cx, cy});
            debug(cx, cy);
         }
         reverse(res.begin(), res.end());
         cout << res.size() << '\n';
         for (auto el : res) {
            cout << el.x + 1 << ' ' << el.y + 1 << '\n';
         }
         break;
      }
   }
   if (!found) cout << -1 << '\n';
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
