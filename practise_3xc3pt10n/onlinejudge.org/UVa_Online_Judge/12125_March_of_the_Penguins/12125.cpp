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

#define debug(args...) { \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = 555;
const int infi = (int)1e9;

int f[N][N], _f[N][N];
vector < vector <int> > Adj;
int Par[N];
int n, m;
long double eps = 1e-9, D;

struct point {
   int xx, yy, np, mxNoJump;
   inline bool canJump (const point &o) {
      return hypot (xx - o.xx, yy - o.yy) < D + eps;
   }
};
vector <point> Point;

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
         debug(cur, f[prv][cur], f[cur][prv], newFlow);
         cur = prv;
      }
   }
   return flow;
}

inline void addEdge (int u, int v, int flow) {
   Adj[u].push_back(v);
   Adj[v].push_back(u);
   _f[u][v] = flow;
}

int nn, s, totalPenguins = 0;
bool solve(int t) {
   int flow = edmondsKarp(s,t);
   return (flow == totalPenguins);
}

void read() {
   Adj.assign(N, vector <int> ());
   Point.clear();
   totalPenguins = 0;

   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
         f[i][j] = _f[i][j] = 0;

   cin >> nn >> D;

   n = 2 * nn + 1, s = n - 1;
   int xx, yy, np, mxNoJump;
   for (int i = 0; i < nn; ++i) {
      cin >> xx >> yy >> np >> mxNoJump;
      Point.push_back({xx, yy, np, mxNoJump});
      addEdge(s, 2 * i, np);
      addEdge(2 *i, 2 * i + 1, mxNoJump);
      totalPenguins += np;
   }

   for (int i = 0; i < nn; ++i) {
      for (int j = 0; j < nn; ++j) {
         if (i == j) continue;
         if (Point[i].canJump(Point[j])) {
            addEdge(2 * i + 1, 2 * j, infi);
         }
      }
   }
   bool ok = false;
   for (int i = 0, cnt = 0; i < nn; ++i) {
      for (int ii = 0; ii < n; ++ii)
         for (int jj = 0; jj < n; ++jj)
            f[ii][jj] = _f[ii][jj];

      if (solve(2 * i)) {
         if (cnt) cout << ' ';
         ++cnt;
         cout << i;
         ok = true;
      }
   }
   if (ok) cout << '\n';
   if (!ok) cout << -1 << '\n';
}

signed main() {
   int tc;
   cin >> tc;
   while (tc--) {
      read();
   }


   return EXIT_SUCCESS;
}

