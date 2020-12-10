#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (7); cout << fixed
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
   long double walkSpeed, ugSpeed;
   cin >> walkSpeed >> ugSpeed;

   int N;
   cin >> N;
   vector <pair <long double, long double>> stationsPos(N + 2);
   for (int i = 0; i < N; ++i) {
      cin >> stationsPos[i].first >> stationsPos[i].second;
   }

   vector <vector <pair <int, long double>>> g;
   g.assign(N + 2, vector <pair <int, long double>> ());

   auto getCost = [&] (int u, int v, long double speed) {
      long double xDist = stationsPos[u].first - stationsPos[v].first;
      long double yDist = stationsPos[u].second - stationsPos[v].second;
      return hypot(xDist, yDist) / speed;
   };

   auto addEdge = [&] (int u, int v, long double speed) {
      long double cost = getCost(u, v, speed);
      g[u].push_back(make_pair(v, cost));
      g[v].push_back(make_pair(u, cost));
      debug("Added edges", u, v, cost);
   };

   int u, v;
   while(cin >> u >> v, u | v) {
      --u, --v;
      addEdge(u, v, ugSpeed);
   }
   for (int i = N; i < N + 2; ++i) {
      cin >> stationsPos[i].first >> stationsPos[i].second;
   }
   for (int i = 0; i < N + 2; ++i) {
      for (int j = i + 1; j < N + 2; ++j) {
         addEdge(i, j, walkSpeed);
      }
   }

   using elem = pair <long double, int>;
   priority_queue <elem, vector <elem>, greater <elem>> pq;
   const long double inf = 1e9;
   const long double eps = 1e-9;
   vector <long double> dist(N + 2, inf);
   vector <bool> vis(N + 2);
   vector <int> pi(N + 2, -1);
   dist[N] = 0.0;
   pq.push(make_pair(dist[N], N));

   while (!pq.empty()) {
      auto topElem = pq.top();
      u = topElem.second;
      debug(u);
      pq.pop();

      if (vis[u]) { continue; }
      vis[u] = true;

      for (auto vp : g[u]) {
         v = vp.first;
         long double w = vp.second;
         assert(fabs(w - vp.second) < eps);
         debug(u, v, w);

         if (!vis[v] and dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            pi[v] = u;
            pq.push(make_pair(dist[v], v));
         }
      }
   }

   assert(fabs(dist[N + 1] - inf) > eps);
   cout << dist[N + 1] << '\n';
   int curVer = N + 1;
   vector <int> path;
   while (pi[curVer] != N) {
      curVer = pi[curVer];
      path.push_back(curVer);
   }
   cout << path.size() << ' ';
   reverse(path.begin(), path.end());
   for (int p : path) {
      cout << p + 1 << ' ';
   }
   cout << endl;
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
