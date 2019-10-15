#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;

const int N = (int)1e4 + 10;

struct Edge {
   int u, v;
   int w;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};

int n, m;
int rep[N], rnk[N];
vector <Edge> edges;

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

int kruskals () {
   int cost = 0;
   int cnt = 0;
   sort (edges.begin(), edges.end());
   makeSet();

   for (Edge e : edges) {
      int u = e.u, v = e.v, w = e.w;
      if (findSet(u) == findSet(v)) continue;
      cost += w;
      mergeSet(u, v);
      ++cnt;
   }
   assert (cnt == n - 1);
   return cost;
}

void solve() {
   assert (edges.size() % 2 == 0);
   cout << kruskals() << '\n';
}

void read() {
   cin >> n;
   edges.clear();
   string s;
   int v, w;
   for (int u = 0; u < n; ++u) {
      cin >> s >> m;
      while (m--) {
         cin >> v >> w;
         --v;
         edges.push_back({u, v, w});
      }
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

