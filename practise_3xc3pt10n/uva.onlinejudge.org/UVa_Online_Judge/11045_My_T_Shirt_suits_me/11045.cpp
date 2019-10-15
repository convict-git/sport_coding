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
using pii = pair <int,int>;

const int N = 6 + 30 + 2;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
int Par[N];
int n, mm;
map <string, int> mp = {{"XS", 0}, {"S", 1}, {"M", 2}, {"L", 3}, {"XL", 4}, {"XXL", 5}};

int bfs (int s, int t) {
   fill (Par, Par + N, -1);
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

void solve() {
   int totalTee, s, t;
   cin >> totalTee >> mm;
   cerr << bg(totalTee) << ' ' << bg(mm) << '\n';
   n = mm + 6 + 2;
   Adj.assign(N, vector <int> ());

   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
         f[i][j] = 0;

   s = 30 + 6, t = 30 + 6 + 1;

   string st;
   for (int i = 0; i < mm; ++i) {
      for (int j = 0; j < 2; ++j) {
         cin >> st;
         //cerr << bg(st) << '\n';
         int u = mp[st], v = i + 6;
         Adj[u].push_back(v);
         Adj[v].push_back(u);
         f[u][v] = 1;
      }
   }

   for (int i = 0; i < 6; ++i) {
      Adj[s].push_back(i);
      Adj[i].push_back(s);
      f[s][i] = totalTee/6;
   }

   for (int i = 6; i < mm + 6; ++i) {
      Adj[i].push_back(t);
      Adj[t].push_back(i);
      f[i][t] = 1;
   }
   int flow = edmondsKarp(s, t);
   //cerr << bg(flow) << ' ' << bg(mm) << '\n';
   if (flow == mm) {
      cout << "YES\n";
   }
   else cout << "NO\n";
}

signed main() {
   int tc;
   cin >> tc;
   while (tc--) {
      solve();
   }

   return EXIT_SUCCESS;
}

