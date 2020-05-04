#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    "[ " << #x << " : " << x << " ]"
#define x        first
#define y        second
using namespace std;
using ld = long double;
using pild = pair <int, long double>;

const int N = 1005;
const long double eps = 1e-9;

vector < vector < pild> > Adj;
vector < vector < int > > ConComp;
vector <pair <ld, ld>> point;
int n, r, cn, CC[N];
bool vis[N];

struct Edge {
   int u, v;
   long double w;
   inline bool operator < (const Edge &o) const {
      return w  + eps < o.w;
   }
};

vector <Edge> edges;
int rep[N], rnk[N];

void makeSet() {
   for(int i = 0; i < n; ++i)
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

long double kruskals () {
   long double cost = 0;
   sort (edges.begin(), edges.end());
   int cnt = 0;

   for (Edge e : edges) {
      int u = e.u, v = e.v;
      long double w = e.w;
      if (findSet(u) == findSet(v)) continue;
      cost += w;
      mergeSet(u, v);
      ++cnt;
   }

   return cost;
}

inline long double wt (int u, int v) {
   ld w = hypot(point[u].x - point[v].x, point[u].y - point[v].y);
   return w;
}

void dfs (int u, int cc) {
   vis[u] = true;
   CC[u] = cc;
   ConComp[cc].push_back(u);
   for (auto vPair : Adj[u]) {
      int v = vPair.x;
      if (!vis[v]) dfs (v, cc);
   }
}

void solve(int tc) {
   cn = 0;
   fill(vis, vis + n, false);
   fill(CC, CC + n, -1);

   for (int i = 0; i < n; ++i) {
      if (!vis[i]) dfs (i, cn++);
   }

   cout << "Case #" << tc << ": " << cn << ' ';

   makeSet();
   ld ans = 0;
   for (int i = 0; i < cn; ++i) {
      edges.clear();
      for (int j = 0; j < (int)ConComp[i].size(); ++j) {
         for (int k = j + 1; k < (int)ConComp[i].size(); ++k) {
            int u = ConComp[i][j], v = ConComp[i][k];
            edges.push_back({u, v, wt(u, v)});
         }
      }
      ans += kruskals();
   }
   cout << (int)(ans + 0.5) << ' ';

   edges.clear();

   for (int u = 0; u < n; ++u) {
      for (int v = 0; v < n; ++v) {
         if (u == v || wt(u, v) < r + eps) continue;
         ld w = wt(u, v);
         edges.push_back({u, v, w});
      }
   }

   ans = kruskals();
   cout << (int)(ans + 0.5) << '\n';
}

void read() {
   cin >> n >> r;
   Adj.assign(n, vector <pild> ());
   point.assign(n, pair <ld, ld>());
   ConComp.assign(n, vector <int> ());
   for (int i = 0; i < n; ++i) {
      cin >> point[i].x >> point[i].y;
   }

   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
         if (i == j) continue;
         if (wt(i, j) < r + eps) {
            Adj[i].push_back(pild(j, wt(i, j)));
            Adj[j].push_back(pild(i, wt(i, j)));
         }
      }
   }
}

signed main() {
   int tc;
   cin >> tc;
   for (int i = 1; i <= tc; ++i) {
      read();
      solve(i);
   }

   return EXIT_SUCCESS;
}

