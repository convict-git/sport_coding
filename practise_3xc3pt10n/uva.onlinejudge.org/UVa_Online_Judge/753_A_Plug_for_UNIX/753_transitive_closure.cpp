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

const int N = 1000 + 10;
const int infi = (int)1e9;

using pss = pair <string, string>;
using pii = pair <int, int>;

vector <string> recept;
vector <pss> appliance, adaptor;
int rec, app, adap;
int W[N][N];
map <string, int> adapMap;
int adap_unique_vertices;

bool vis[N];
int match[N];
vector < vector <int> > Adj;
int n, nl, nr; // first 0, ..., nl - 1 vertices in left nl, ..., nr - 1 in right

void init_mcbm() {
   n = nl + nr;
   assert(n);
   Adj.assign(n, vector <int> ());
   for (int i = 0; i < n; ++i)
      vis[i] = false, match[i] = -1;
}

inline void add_edge(int u, int v) {
   Adj[u].push_back(v);
}

bool augment(int u) {
   if (vis[u]) return false;
   vis[u] = true;

   for (int v : Adj[u]) {
      if (match[v] == -1 || augment(match[v])) {
         match[v] = u;
         return true;
      }
   }
   return false;
}

int MCBM() {
   assert (nl + nr == n);
   int mcbm = 0;

   for (int u = 0; u < nl; ++u) { // in left set
      fill(vis, vis + n, false);
      mcbm += augment(u);
   }
   return mcbm;
}

void init() {
   recept.clear();
   appliance.clear();
   adaptor.clear();
   adapMap.clear();
}

void transitive_closure() {
   for (int i = 0; i < adap_unique_vertices; ++i)
      for (int j = 0; j < adap_unique_vertices; ++j)
         W[i][j] = i == j ? 1 : 0;

   for (int i = 0; i < adap; ++i) {
      int u = adapMap[adaptor[i].x], v = adapMap[adaptor[i].y];
      W[u][v] = 1;
   }

   for (int k = 0; k < adap_unique_vertices; ++k) {
      for (int i = 0; i < adap_unique_vertices; ++i) {
         for (int j = 0; j < adap_unique_vertices; ++j) {
            W[i][j] |= (W[i][k] && W[k][j]);
         }
      }
   }
}

void solve() {
   nl = app, nr = rec;
   init_mcbm();
   for (int i = 0; i < rec; ++i) {
      for (int j = 0; j < app; ++j) {
         int u = adapMap[appliance[j].y], v = adapMap[recept[i]];
         if (W[u][v]) add_edge(j, i);
      }
   }
   int mcbm = MCBM();
   cout << app - mcbm << '\n';
}

void add_string_in_map(const string &st) {
   if (adapMap.find(st) == adapMap.end())
      adapMap[st] = adap_unique_vertices++;
}

void read() {
   init();
   cin >> rec;
   string st_a, st_b;
   adap_unique_vertices = 0;
   for (int i = 0; i < rec; ++i) {
      cin >> st_a;
      recept.push_back(st_a);
      add_string_in_map(st_a);
   }

   cin >> app;
   for (int i = 0; i < app; ++i) {
      cin >> st_a >> st_b;
      appliance.push_back(pss(st_a, st_b));

      add_string_in_map(st_a);
      add_string_in_map(st_b);
   }

   cin >> adap;
   for (int i = 0; i < adap; ++i) {
      cin >> st_a >> st_b;
      adaptor.push_back(pss(st_a, st_b));

      add_string_in_map(st_a);
      add_string_in_map(st_b);
   }
   assert ((int) adapMap.size() == adap_unique_vertices);
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      transitive_closure();
      solve();
      if (tc) cout << '\n';
   }

   return EXIT_SUCCESS;
}


