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

const int N = 2 * 1001 + 10;
int rows, cols, enemy_count;

bool vis[N];
int match[N];
vector < vector <int> > Adj;
int n, nl, nr; // first 0, ..., nl - 1 vertices in left nl, ..., nr - 1 in right

void init() {
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

bool KL[N], KR[N];
bool alternate(int u) {
   KL[u] = true;
   for (int v : Adj[u]) {
      KR[v] = true;
      alternate(match[v]);
   }
}

void solve() {
   int mcbm = MCBM();
   cout << mcbm << '\n';
}

void read() {
   nl = rows, nr = cols;
   init();
   int r, c;
   for (int i = 0; i < enemy_count; ++i) {
      cin >> r >> c;
      --r, --c;
      add_edge(r, c);
   }
}

signed main() {
   IOS; PREC;
   while (cin >> rows >> cols >> enemy_count, rows || cols || enemy_count) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

