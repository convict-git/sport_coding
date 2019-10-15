#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ]"
#define x        first
#define y        second

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
const int N = 100 + 2 * 100 + 100 + 2;
const int infi = (int)1e9;

using pss = pair <string, string>;
using pii = pair <int, int>;

vector <string> recept;
vector <pss> appliance, adaptor;
int rec, app, adap;

vector < vector <int> > Adj;
vector <pii> cutEdges;
bool inS[N];
int Par[N];
int cap[N][N], fcap[N][N];
int n, m;

void init () {
   assert(n);
   Adj.assign(n, vector <int> ());
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         fcap[i][j] = cap[i][j] = 0;
   cutEdges.clear();
   fill (inS, inS + n, false);
}

int bfs (const int &s, const int &t) {
   fill (Par, Par + n, -1);
   Par[s] = -2;

   queue <pii> Q;
   Q.push(pii(s, infi));

   while (!Q.empty()) {
      pii tmp = Q.front();
      Q.pop();
      int u = tmp.x, flow = tmp.y;

      for (int v : Adj[u]) {
         if (Par[v] == -1 && fcap[u][v]) {
            Par[v] = u;
            int newFlow = min(flow, fcap[u][v]);
            if (v == t) {
               return newFlow;
            }
            Q.push(pii(v, newFlow));
         }
      }
   }
   return 0;
}

int edmondsKarpMaxFlow(const int &s, const int &t, const int &K = infi) {
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         fcap[i][j] = cap[i][j];

   int flow = 0;
   int newFlow;

   while ((newFlow = bfs (s, t)) && flow < K) {
      newFlow = min(newFlow, K - flow);
      flow += newFlow;
      int cur = t;
      while (cur != s) {
         int prv = Par[cur];
         fcap[prv][cur] -= newFlow;
         fcap[cur][prv] += newFlow;
         cur = prv;
      }
   }

   assert (flow < K);
   // assert (flow != 0);
   return flow;
}

void dfs(int u) {
   inS[u] = true;
   for (int v : Adj[u])
      if (!inS[v]) dfs(v);
}

void findCutEdges() {
   cutEdges.clear();
   for (int u = 0; u < n; ++u) {
      if (!inS[u]) continue;
      for (int v : Adj[u]) {
         if (inS[v]) continue;
         if (fcap[u][v] == 0) cutEdges.push_back(pii(u, v));
      }
   }
}

inline void add_edge (int u, int v, int flow) {
   Adj[u].push_back(v);
   Adj[v].push_back(u);
   cap[u][v] = flow;
}
void v_init() {
   recept.clear();
   appliance.clear();
   adaptor.clear();
}

int s, t;
void solve() {
   int flow = edmondsKarpMaxFlow(s, t);
   cout << app - flow << '\n';
}

void create_edges() {
   n = rec + app + 2 * adap + 2;
   s = n - 2, t = n - 1;
   init();

   // edges for receptacle with target
   for (int i = 0; i < rec; ++i)
      add_edge (i, t, 1);


   /****BE AWARE>>>>adapters are infinite so you can take as many*****/
   // edge for adaptor among themselves
   for (int i = 0; i < adap; ++i) {
      add_edge (2 * i + rec, 2 * i + 1 + rec, infi);

      for (int j = 0; j < adap; ++j) {
         if (i == j) continue;
         if (adaptor[i].y == adaptor[j].x)
            add_edge (2 * i + 1 + rec, 2 * j + rec, infi);
      }
   }

   // edge for adaptors and receptacles
   for (int i = 0; i < adap; ++i) {
      for (int j = 0; j < rec; ++j) {
         if (adaptor[i].y == recept[j]) add_edge (2 * i + 1 + rec, j, infi);
      }
   }

   // edges for appliance
   for (int i = 0; i < app; ++i) {
      add_edge (s, i + rec + 2 * adap, 1);

      for (int j = 0; j < rec; ++j) {
         if (appliance[i].y == recept[j]) add_edge (i + rec + 2 * adap, j, infi);
      }

      for (int j = 0; j < adap; ++j) {
         if (appliance[i].y == adaptor[j].x) add_edge(i + rec + 2 * adap, 2 * j + rec, infi);
      }
   }
}

void read() {
   v_init();
   cin >> rec;
   string st_a, st_b;
   for (int i = 0; i < rec; ++i) {
      cin >> st_a;
      recept.push_back(st_a);
   }

   cin >> app;
   for (int i = 0; i < app; ++i) {
      cin >> st_a >> st_b;
      appliance.push_back(pss(st_a, st_b));
   }

   cin >> adap;
   for (int i = 0; i < adap; ++i) {
      cin >> st_a >> st_b;
      adaptor.push_back(pss(st_a, st_b));
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      create_edges();
      solve();
      if (tc) cout << '\n';
   }

   return EXIT_SUCCESS;
}


