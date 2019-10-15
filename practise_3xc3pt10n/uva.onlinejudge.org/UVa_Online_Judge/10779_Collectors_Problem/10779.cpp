//TODO with less vertices merge all mm * i + j in one for each i, i.e. merge j vertex to one for each player except bob
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

const int N = 10 * 25 + 2;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
int n, m, nn, mm;
int Par[N];

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

void addEdge (int u, int v, int flow) {
   Adj[u].push_back(v);
   Adj[v].push_back(u);
   f[u][v] = flow;
}

void solve(int tc) {
   int s, t;
   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
         f[i][j] = 0;

   cin >> nn >> mm;
   n = nn * mm + 2;
   s = nn * mm, t = nn * mm + 1;
   Adj.assign(n, vector <int> ());

   int val[25];
   for (int i = 0; i < nn; ++i) {
      fill (val, val + 25, 0);
      int ki, kval;
      cin >> ki;
      while (ki--) {
         cin >> kval;
         --kval;
         val[kval] += 1;
      }
      for (int j = 0; j < mm; ++j) {
         int w = val[j];
         if (i == 0) {
            addEdge (s, j, w);
            addEdge (j, t, 1);
         }
         else {
            w -= 1;
            if (w > 0)
               addEdge(mm * i + j, j, w);
            else if (w < 0)
               addEdge(j, mm * i + j, -w);
         }
      }

      if (i) {
         for (int j = 0; j < mm; ++j) {
            for (int k = j + 1; k < mm; ++k) {
               addEdge (mm * i + j, mm * i + k, 1);
               addEdge (mm * i + k, mm * i + j, 1);
            }
         }
      }
   }
   cout << "Case #" << tc << ": " << edmondsKarp(s, t) << '\n';;
}

signed main() {
   int tc;
   cin >> tc;
   for (int i = 1; i <= tc; ++i) {
      solve(i);
   }

   return EXIT_SUCCESS;
}

