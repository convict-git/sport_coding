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
const int N = 26 + 10 + 2;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
int n, m;
int Par[N];

int bfs (int s, int t) {
   fill (Par, Par + 10 + 26 + 2, -1);
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

bool edmondsKarp(int s, int t, int K) {
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
   if (flow != K) return false;

   for (int v = 0; v < 10; ++v) {
      bool ok = false;
      for (int u = 10; u < 10 + 26; ++u) {
         if (f[v][u] == 1) {
            cout << char(u - 10 + 'A');
            ok = true;
         }
      }
      if (!ok) cout << "_";
   }
   cout << '\n';
   return true;
}

void read() {
   string st;
   int s = 10 + 26, t = 10 + 26 + 1, K = 0;
   Adj.assign(26 + 10 + 2, vector <int> ());
   bool new_test = true;

   while (true) {
      getline(cin, st);
      bool eoff = !cin;
      if (eoff || st[0] - 'A' == -65) {
         if (!edmondsKarp(s, t, K)) cout << "!\n";
         new_test = true;
         if (eoff) break;
         continue;
      }
      if (new_test) {
         new_test = false;
         Adj.assign(10 + 26 + 2, vector <int> ());

         for (int u = 0; u < 10; ++u) {
            Adj[t].push_back(u);
            Adj[u].push_back(t);
         }

         for (int v = 10; v < 10 + 26; ++v) {
            Adj[v].push_back(s);
            Adj[s].push_back(v);
         }
         for (int u = 0; u < (10 + 26 + 2); ++u) {
            for (int v = 0; v < (10 + 26 + 2); ++v) {
               f[u][v] = 0, f[v][u] = 0;
            }
         }
         K = 0;
      }

      int u = st[0] - 'A' + 10, k = st[1] - '0';
      f[s][u] = k;
      K += k;

      assert(st[2] == ' ');

      int v;
      for (int i = 3; st[i] != ';'; ++i) {
         v = st[i] - '0';
         f[u][v] = infi;
         f[v][t] = 1;
         Adj[u].push_back(v);
         Adj[v].push_back(u);
      }
   }
}

signed main() {
   read();
   return EXIT_SUCCESS;
}

