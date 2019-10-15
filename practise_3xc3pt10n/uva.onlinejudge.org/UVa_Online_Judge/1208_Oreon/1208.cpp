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

const int N = 27;

struct Edge {
   int u, v;
   int w;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};

vector <Edge> edges;
vector <Edge> MST;
int rep[N], rnk[N];
int n;

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
      MST.push_back({u, v, w});
      ++cnt;
   }

   assert (cnt == n - 1);
   return cost;
}


bool comp (const Edge& e1, const Edge& e2) {
   return (e1.u < e2.u || (e1.u == e2.u && e1.v > e2.v));
}
void solve(int tc) {
   int ans = kruskals();
   //sort (MST.begin(), MST.end(), comp);
   cout << "Case " << tc << ":\n";
   for (Edge e : MST) {
      cout << (char) (e.u + 'A') << '-' << (char)(e.v + 'A') << ' ' << e.w << '\n';
   }
   cerr << tc << '\n';
}

void read() {
   cin >> n;
   edges.clear();
   MST.clear();
   int w;
   string s;
   char c;
   getchar();
   for (int i = 0; i < n; ++i) {
      getline(cin, s);
      stringstream ss(s);
      for (int j = 0; j < n; ++j) {
         ss >> w >> c;
         int u = min(i, j), v = max(i, j);
         if (w != 0) edges.push_back({u, v, w});
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

