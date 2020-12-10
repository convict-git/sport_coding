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

const int Maxn = 2e3 + 10;
int N, M, source, dest;
vector <int> g[Maxn];
int sDist[Maxn], tDist[Maxn];
int Mat[Maxn][Maxn];

void preproc()
{
}

void shortestPath (int sourcesVertex, int *distArray) {
   for (int i = 0; i < N; ++i) {
      distArray[i] = INT_MAX;
   }
   vector <int> vis(N);
   distArray[sourcesVertex] = 0;

   queue <int> bfsQueue;
   bfsQueue.push(sourcesVertex);

   while (!bfsQueue.empty()) {
      int uPop = bfsQueue.front();
      bfsQueue.pop();

      if (vis[uPop]) continue;
      vis[uPop] = true;

      assert(distArray[uPop] != INT_MAX);
      for (int v : g[uPop]) {
         if (!vis[v] and distArray[v] > distArray[uPop] + 1) {
            distArray[v] = distArray[uPop] + 1;
            bfsQueue.push(v);
         }
      }
   }
}

void solve()
{
   memset(Mat, 0, sizeof(Mat));
   cin >> N >> M >> source >> dest;
   --source, --dest;

   while (M--) {
      int u, v;
      cin >> u >> v; --u, --v;
      g[u].push_back(v);
      g[v].push_back(u);
      Mat[u][v] = Mat[v][u] = 1;
   }
   shortestPath(source, sDist);
   shortestPath(dest, tDist);

   assert(sDist[dest] == tDist[source]);
   int stDistance = sDist[dest]; // always happends

   int res = 0;
   for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
         if (!Mat[i][j]) {
            if (sDist[i] + tDist[j] + 1 >= stDistance
                  and
                  sDist[j] + tDist[i] + 1 >= stDistance)
            {
               ++res;
            }
         }
      }
   }
   cout << res << '\n';
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
