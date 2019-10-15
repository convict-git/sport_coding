#include         <bits/stdc++.h>
#define x        first
#define y        second
#define b(x)   "[ " << #x << " : " << x << " ]"
using namespace std;
using pii = pair<int, int>;
const int N = (int)1e3 + 10;

int n, m, k;
int rep[N], rnk[N], sz[N];
bool isGov[N], repGov[N], isRep[N];
vector <pii> edges;

void makeSet() {
   for(int i = 0; i < n; ++i)
      rep[i] = i, rnk[i] = 0, sz[i] = 1, isRep[i] = true;
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
inline int nc2 (int t) { return (t * (t - 1))/2; }

void mergeSet(int u, int v) {
   int ru = findSet(u), rv = findSet(v);
   if (rnk[ru] > rnk[rv]) {
      rep[rv] = rep[ru];
      sz[ru] += sz[rv];
      isRep[ru] = true, isRep[rv] = false;
   }
   else {
      rep[ru] = rep[rv];
      sz[rv] += sz[ru];
      isRep[rv] = true, isRep[ru] = false;
   }

   if (rnk[ru] == rnk[rv]) {
      ++rnk[rv];
   }
}

void solve() {
   makeSet();
   int u, v;
   for (int i = 0; i < m; ++i) {
      u = edges[i].x, v = edges[i].y;
      if (findSet(u) == findSet(v)) continue;
      mergeSet(u, v);
   }

   for (int i = 0; i < n; ++i) {
      if (isGov[i]) {
         repGov[rep[i]] = true;
      }
   }

   int vx = 0, ed = 0;

   for (int i = 0; i < n; ++i) {
      if(isRep[i] && !repGov[i]) {
         vx += sz[i];
      }
   }
   ed = nc2(vx);

   int ans = 0;
   int mx = 0, mxIdx = -1;
   for (int i = 0; i < n; ++i)
      if (repGov[i])
         if (mx < sz[i])
            mx = sz[i], mxIdx = i;

   for (int i = 0; i < n; ++i)
      if (repGov[i] && i != mxIdx)
         ans += nc2(sz[i]);

   ans += nc2(sz[mxIdx] + vx);
   cout << ans - m << '\n';
}

void read() {
   int u, v;
   edges.clear();
   fill (isGov, isGov + n, false);
   fill (repGov, repGov + n, false);

   for (int i = 0; i < k; ++i) {
      cin >> u;
      --u;
      isGov[u] = true;
   }

   for (int i = 0; i < m; ++i)  {
      cin >> u >> v;
      --u, --v;
      edges.push_back(pii(u, v));
   }
}

signed main() {
   while (cin >> n >> m >> k) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}
