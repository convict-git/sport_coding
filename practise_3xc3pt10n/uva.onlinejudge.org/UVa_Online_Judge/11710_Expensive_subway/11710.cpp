#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
const int N = 505;
const int infi = (int)1e9;

struct Edge {
   int u, v;
   int w;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};

vector <Edge> edges;
int n, m;
int rep[N], rnk[N];
map <string, int> mp;

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

int kruskals () { int cost = 0, cnt = 0;
   sort (edges.begin(), edges.end());
   makeSet();

   for (Edge e : edges) {
      int u = e.u, v = e.v;
      int w = e.w;
      if (findSet(u) == findSet(v)) continue;
      cost += w;
      mergeSet(u, v);
      ++cnt;
   }
   return (cnt == n - 1 ? cost : infi);
}

void solve() {
   int ans = kruskals();
   if (ans == infi) cout << "Impossible\n";
   else cout << ans << '\n';
}

void read() {
   string su, sv;
   int u, v, w;
   edges.clear();
   mp.clear();
   for (int i = 0; i < n; ++i) {
      cin >> su;
      mp[su] = i;
   }
   for (int i = 0; i < m; ++i) {
      cin>> su >> sv >> w;
      u = mp[su], v = mp[sv];
      edges.push_back({u, v, w});
   }
   cin >> su;
}

signed main() {
   while (cin >> n >> m, n || m) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

