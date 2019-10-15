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
using pii = pair <int, int>;

const int N = 2010;
const int infi = (int)1e9;

struct Edge {
   int u, v;
   int w;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};

vector <string> S;
vector <Edge> MST;
vector <Edge> edges;
int rep[N], rnk[N];
int n, m;

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
   sort (edges.begin(), edges.end());
   makeSet();
   int cnt = 0;

   for (Edge e : edges) {
      int u = e.u, v = e.v;
      int w = e.w;
      if (findSet(u) == findSet(v)) continue;
      cost += w;
      mergeSet(u, v);
      MST.push_back(e);
      ++cnt;
   }

   assert (cnt == n - 1);
   return cost;
}

inline int wgt(const string &s1, const string &s2) {
   assert(s1.size() == s2.size());
   int w = -infi;
   for (int i = 0; i < m; ++i) {
      w = max(w, abs(s1[i] - s2[i]));
   }
   return w;
}

void solve() {
   for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
         edges.push_back({i, j, wgt(S[i], S[j])});
      }
   }
   kruskals();
   int mx = -infi;
   for (Edge e : MST)
      mx = max(mx, e.w);
   cout << mx << '\n';
}

void read() {
   edges.clear();
   S.clear();
   MST.clear();
   string s;
   for (int i = 0; i < n; ++i) {
      cin >> s;
      S.push_back(s);
   }
}

signed main() {
   while (cin >> n >> m) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

