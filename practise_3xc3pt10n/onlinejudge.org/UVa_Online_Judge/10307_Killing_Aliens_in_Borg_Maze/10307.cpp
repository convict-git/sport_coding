#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = 55;
const int infi = (int)1e9;

struct Edge {
   int u, v, w;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};

int n, m;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
vector <string> C;
int d[N * N][N * N];
vector <Edge> edges;


int rep[N * N], rnk[N * N];

void makeSet() {
   for(int i = 0; i < n * m; ++i)
      rep[i] = i, rnk[i] = 0;
}

int findSet(int u) {
   int ru = u;
   while (ru != rep[ru])
      ru = rep[ru];

   while (u != rep[u]) {
      int tmp = rep[u];
      rep[u] = ru;
      u = tmp;
   }
   return ru;
}

void mergeSet(int u, int v) {
   int ru = findSet(u), rv = findSet(v);
   if (rnk[ru] > rnk[rv]) rep[rv] = rep[ru];
   else rep[ru] = rep[rv];

   if (rnk[ru] == rnk[rv])
      ++rnk[rv];
}

int kruskals () {
   int cost = 0;
   sort (edges.begin(), edges.end());
   makeSet();

   for (Edge e : edges) {
      int u = e.u, v = e.v, w = e.w;
      if (findSet(u) == findSet(v)) continue;
      cost += w;
      mergeSet(u, v);
   }
   return cost;
}

inline bool isValid(int xx, int yy) {
   return xx >= 0 && yy >= 0 && xx < n && yy < m && C[xx][yy] != '#';
}

void bfs (int xx, int yy, int ds[]) {
   bool vis[N][N];
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
      vis[i][j] = 0, ds[m * i + j] = infi;

   ds[m * xx + yy] = 0;
   queue <pii> Q;
   Q.push(pii(xx, yy));
   while (!Q.empty()) {
      pii u = Q.front();
      Q.pop();
      assert (ds[m * u.x + u.y] != infi);

      for (int dir = 0; dir < 4; ++dir) {
         int vx = u.x + dx[dir], vy = u.y + dy[dir];
         if (!isValid(vx, vy)) continue;

         if (ds[m * vx + vy] > ds[m * u.x + u.y] + 1) {
            ds[m * vx + vy] = ds[m * u.x + u.y] + 1;
            Q.push(pii(vx, vy));
         }
      }
   }
}

void solve() {
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
         if (C[i][j] == 'A' || C[i][j] == 'S') {
            bfs (i, j, d[m * i + j]);
            for (int ii = 0; ii < n; ++ii) {
               for (int jj = 0; jj < m; ++jj) {
                  if ((i == ii && j == jj) || (C[ii][jj] != 'A' && C[ii][jj] != 'S')) continue;
                  int u = m * i + j, v = m * ii + jj, w = d[u][v];
                  edges.push_back({u, v, w});
               }
            }
         }
      }
   }
   int ans = kruskals();
   cout << ans << '\n';
}

void read() {
   cin >> m >> n;
   C.clear();
   edges.clear();
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
         d[i][j] = infi;

   string S;
   getchar();
   for (int i = 0; i < n; ++i) {
      getline(cin, S);
      C.push_back(S);
   }
}

signed main() {
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

