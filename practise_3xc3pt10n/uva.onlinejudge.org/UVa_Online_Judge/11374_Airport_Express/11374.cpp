#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = (int)1e3 + 10;
const int infi = (int)1e9;

int n, m1, m2, src, tar;
vector <vector <pii> > AdjEco, AdjCom;
int dist[N][2], vis[N][2], ticket[N];
pii Par[N][2];

struct el {
   int v, d, state;
   inline bool operator > (const el &p) const {
      return d > p.d;
   }
};

void dijkstra () {
   for (int i = 0; i < n; ++i) {
      ticket[i] = -1;
      dist[i][0] = dist[i][1] = infi;
      vis[i][0] = vis[i][1] = false;
      Par[i][0] = Par[i][1] = pii(-1, -1);
   }

   dist[src][0] = 0;
   priority_queue <el, vector <el>, greater <el> > Q;
   Q.push({src, dist[src][0], 0});

   while (!Q.empty()) {
      el tmp = Q.top();
      Q.pop();

      int u = tmp.v, state = tmp.state;
      if (vis[u][state]) continue;
      vis[u][state] = true;

      for (auto vPair : AdjEco[u]) {
         int v = vPair.x;
         int w = vPair.y;

         if (!vis[v][state] && dist[v][state] > dist[u][state] + w) {
            dist[v][state] = dist[u][state] + w;
            if (state) ticket[v] = ticket[u];
            Par[v][state] = pii(u, state);
            Q.push({v, dist[v][state], state});
         }
      }

      if (state == 0) {
         for (auto vPair : AdjCom[u]) {
            int v = vPair.x;
            int w = vPair.y;

            if (!vis[v][1] && dist[v][1] > dist[u][0] + w) {
               dist[v][1] = dist[u][0] + w;
               ticket[v] = u + 1;
               Par[v][1] = pii(u, 0);
               Q.push({v, dist[v][1], 1});
            }
         }
      }
   }

   vector <int> Path;
   int u = tar;
   int idx = (dist[tar][0] > dist[tar][1] ? 1 : 0);
   int state = idx;

   while (true) {
      Path.push_back(u);
      if (u == src) break;
      pii tmp = Par[u][state];
      u = tmp.x, state = tmp.y;
   }
   reverse(Path.begin(), Path.end());
   for (int i = 0; i < (int)Path.size(); ++i) {
      cout << Path[i] + 1;
      if (i != (int)Path.size() - 1) cout << ' ';
      else cout << '\n';
   }
   if (idx == 1) cout << ticket[tar] << '\n';
   else cout << "Ticket Not Used\n";
   cout << dist[tar][idx] << '\n';
}

void read() {
   int it = 0;
   while (cin >> n >> src >> tar) {
      if (it) cout << '\n';
      ++it;
      --src, --tar;
      int u, v, w;
      cin >> m1;
      AdjEco.assign(n, vector <pii> ());
      AdjCom.assign(n, vector <pii> ());

      for (int i = 0; i < m1; ++i) {
         cin >> u >> v >> w;
         --u, --v;
         AdjEco[u].emplace_back(pii(v, w));
         AdjEco[v].emplace_back(pii(u, w));
      }
      cin >> m2;

      for (int i = 0; i < m2; ++i) {
         cin >> u >> v >> w;
         --u, --v;
         AdjCom[u].emplace_back(pii(v, w));
         AdjCom[v].emplace_back(pii(u, w));
      }
      dijkstra();
   }
}

signed main() {
   read();

   return EXIT_SUCCESS;
}
