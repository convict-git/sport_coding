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

const int N = 5000;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
int n, m, K;
int Par[N], cat[N];

int bfs (int s, int t) {
   fill (Par, Par + n, -1);
   Par[s] = -2;

   queue <pii> Q;
   Q.push(pii(s, infi));

   while (!Q.empty()) {
      pii tmp = Q.front();
      Q.pop();
      int u = tmp.x, flow = tmp.y;

      for (int v : Adj[u]) {
         if (Par[v] == -1 && f[u][v]) {
            Par[v] = u;
            int newFlow = min(flow, f[u][v]);
            if (v == t) {
               return newFlow;
            }
            Q.push(pii(v, newFlow));
         }
      }
   }
   return 0;
}

int edmondsKarp(int s, int t) {
   int flow = 0;
   int newFlow;

   while ((newFlow = bfs (s, t))) {
      flow += newFlow;
      int cur = t;
      while (cur != s) {
         int prv = Par[cur];
         f[prv][cur] -= newFlow;
         f[cur][prv] += newFlow;
         cur = prv;
      }
   }
   return flow;
}

int nk, np;
void solve(int s, int t) {
   int flow = edmondsKarp(s, t);
   if (flow != K) cout << 0 << '\n';
   else {
      cout << 1 << '\n';
      for (int i = np; i < np + nk; ++i) {
         int cnt = cat[i - np];
         for (int v : Adj[i])  {
            if (i == t) continue;
            if (f[i][v] == 1) {
               --cnt;
               cout << v + 1;
               if (cnt) cout << ' ';
            }
         }
         cout << '\n';
      }
   }
}

pii read() {
   n = np + nk + 2;
   Adj.assign(np + nk + 2, vector <int> ());

   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         f[i][j] = f[j][i] = 0;

   K = 0;
   for (int i = 0; i < nk; ++i) {
      cin >> cat[i];
      K += cat[i];
   }

   int cnt = 0, s, t;
   for (int i = 0; i < np; ++i) {
      cin >> cnt;
      int v;
      while (cnt--) {
         cin >> v;
         --v;
         v += np;
         Adj[i].push_back(v);
         Adj[v].push_back(i);
         f[i][v] = 1;
      }
   }
   s = np + nk, t = np + nk + 1;
   for (int i = 0; i < np; ++i) {
      Adj[s].push_back(i);
      Adj[i].push_back(s);
      f[s][i] = 1;
   }

   for (int i = np; i < np + nk; ++i) {
      Adj[t].push_back(i);
      Adj[i].push_back(t);
      f[i][t] = cat[i - np];
   }
   return pii(s, t);
}

signed main() {
   while (cin >> nk >> np, nk || np) {
      pii tmp = read();
      solve(tmp.x, tmp.y);
   }

   return EXIT_SUCCESS;
}

