#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong
typedef pair <long long ,long long> pii;
const long long N = 210;
const long long infi = 1e18+10;

void preproc() {
}

vector < set <long long> > Adj;
vector <pii> cutEdges;
bool inS[N];
long long Par[N];
long long cap[N][N], fcap[N][N];
long long n, m;

void init () {
   assert(n);
   Adj.assign(n, set <long long> ());
   for (long long i = 0; i < n; ++i)
      for (long long j = 0; j < n; ++j)
         fcap[i][j] = cap[i][j] = 0;
   fill (inS, inS + n, false);
}

long long bfs (const long long &s, const long long &t) {
   fill (Par, Par + n, -1);
   Par[s] = -2;

   queue <pii> Q;
   Q.push(pii(s, infi));

   while (!Q.empty()) {
      pii tmp = Q.front();
      Q.pop();
      long long u = tmp.first, flow = tmp.second;

      for (long long v : Adj[u]) {
         if (Par[v] == -1 && fcap[u][v]) {
            Par[v] = u;
            long long newFlow = min(flow, fcap[u][v]);
            if (v == t) {
               return newFlow;
            }
            Q.push(pii(v, newFlow));
         }
      }
   }
   return 0;
}

long long edmondsKarpMaxFlow(const long long &s, const long long &t) {
   for (long long i = 0; i < n; ++i)
      for (long long j = 0; j < n; ++j)
         fcap[i][j] = cap[i][j];

   long long flow = 0;
   long long newFlow;

   while ((newFlow = bfs (s, t))) {
      flow += newFlow;
      long long cur = t;
      while (cur != s) {
         long long prv = Par[cur];
         fcap[prv][cur] -= newFlow;
         fcap[cur][prv] += newFlow;
         cur = prv;
      }
   }
   return flow;
}

inline void addEdge (long long u, long long v, long long flow) {
   Adj[u].insert(v);
   Adj[v].insert(u);
   cap[u][v] += flow;
   // cerr << u << ' ' << v << ' ' << flow << '\n';
}

void solve() { // flow
   cerr << '\n';
   long long total=0;
   long long Ni;
   cin >> Ni;
   n = 2 * Ni + 2;
   init();
   // V = 2 * n + 2; // start + sink + 2 * number of vertices
   for (long long i = 0, di; i < Ni; ++i) {
      cin >> di;
      total += di;
      addEdge(2*Ni, 2*i, di); // source to start
   }
   for (long long i = 0, pi; i < Ni; ++i) { // between
      cin >> pi;
      addEdge(2*i, 2*i + 1, pi);
   }
   long long S; // safe districts
   cin >> S;
   for (long long i = 0, si; i < S; ++i) {
      cin >> si;
      addEdge(2*si, 2*Ni + 1, infi); // to sink
      addEdge(2*si+1, 2*Ni + 1, infi); // to sink
   }
   long long m1;
   cin >> m1;
   while (m1--) {
      long long u, v, c;
      cin >> u >> v >> c;
      addEdge(2*u + 1, 2*v, c);
   }
   long long m2, g;
   cin >> m2 >> g;
   while (m2--) {
      long long u, v;
      cin >> u >> v;
      addEdge(2*u + 1, 2*v, g);
   }
   long long m3, h;
   cin >> m3 >> h;
   while (m3--) {
      long long u, v;
      cin >> u >> v;
      addEdge(2*u + 1, 2*v, h);
   }
   long long mxflow = edmondsKarpMaxFlow(2*Ni, 2*Ni+1);
   if (mxflow >= total) {
      cout << "All Safe\n";
   }
   else cout << mxflow << '\n';
}

signed main() {
  IOS; PREC;
  preproc();

  long long tc = 1;
  cin >> tc;
  for (long long Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
