#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, long long>;
using pi = pair <int, int>;

const int N = int(1e5) + 10;
const long long inf = (long long) 1e18;

vector < vector <pii> > Adj;
int n, m;
long long dist[N][2];
bool vis[N][2];

class Compare {
   public:
      inline bool operator () (const pi &p, const pi &q) const {
         return dist[p.x][p.y] > dist[q.x][q.y];
      }
};

void dijkstra(int src, int tar) {
   for (int i = 0; i < n; ++i)
      dist[i][0] = inf, dist[i][1] = inf,
         vis[i][0] = vis[i][1] = false;

   dist[src][0] = 0;
   priority_queue < pi, vector<pi>, Compare> Q;
   Q.push(pi(src, 0));

   while (!Q.empty()) {
      pi tmp = Q.top();
      Q.pop();
      int u = tmp.x, state = tmp.y;
      if (vis[u][state]) continue;
      vis[u][state] = true;

      for (auto vPair : Adj[u]) {
         int v = vPair.x;
         long long w = vPair.y;
         int nxtState = state ^ 1;
         if (!vis[v][nxtState] && dist[v][nxtState] > dist[u][state] + w) {
            dist[v][nxtState] = dist[u][state] + w;
            Q.push(pi(v, nxtState));
         }
      }
   }

   if (dist[tar][0] == inf)
      cout << -1 << '\n';
   else cout << dist[tar][0] << '\n';
}

void read() {
   while (cin >> n >> m) {
      int u, v;
      long long w;
      Adj.assign(n, vector <pii> ());

      for (int e = 0; e < m; ++e) {
         cin >> u >> v >> w;
         --u, --v;
         Adj[u].push_back(pii(v, w));
         Adj[v].push_back(pii(u, w));
      }

      dijkstra(0, n - 1);
   }
}

signed main() {
   read();

	return EXIT_SUCCESS;
}

