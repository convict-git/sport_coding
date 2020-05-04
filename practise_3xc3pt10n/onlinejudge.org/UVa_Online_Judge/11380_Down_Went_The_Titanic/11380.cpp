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

const int N = 1800 + 2;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
vector <string> input;
int n, m, P, r, c;
int Par[N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};

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

inline void addEdge (int u, int v, int flow) {
   Adj[u].push_back(v);
   Adj[v].push_back(u);
   f[u][v] = flow;
}

inline bool isValid (int xx, int yy) {
   return xx >= 0 && yy >= 0 && xx < r && yy < c && input[xx][yy] != '~';
}

void solve() {
   Adj.assign(N, vector <int> ());
   input.clear();

   int s = N - 2, t = N - 1;

   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
         f[i][j] = 0;

   string st;
   for (int i = 0; i < r; ++i) {
      cin >> st;
      input.push_back(st);
   }

   for (int i = 0; i < r; ++i) {
      for (int j = 0; j < c; ++j) {
         for (int dir = 0; dir < 4; ++dir) {
            int xx = i + dx[dir], yy = j + dy[dir];
            if (!isValid(xx, yy)) continue;
            addEdge(2 * (c * i + j) + 1, 2 * ( c * xx + yy), infi); // this one was nice
         }
         int u = 2 * (c * i + j), v = 2 * (c * i + j) + 1;

         if (input[i][j] == '*') {
            addEdge(u, v, 1);
            addEdge(s, u, 1);
         }
         else if(input[i][j] == '.') {
            addEdge(u, v, 1);
         }
         else if(input[i][j] == '#') {
            addEdge(u, v, infi);
            addEdge(v, t, P);
         }
         else if(input[i][j] == '@') {
            addEdge(u, v, infi);
         }
      }
   }

   int flow = edmondsKarp(s, t);
   cout << flow << '\n';
}

signed main() {
   while (cin >> r >> c >> P) {
      solve();
   }

   return EXIT_SUCCESS;
}

