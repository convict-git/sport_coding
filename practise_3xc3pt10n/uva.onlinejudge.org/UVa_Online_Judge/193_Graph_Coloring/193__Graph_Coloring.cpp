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


const int N = 104;
vector <int> stck, sol;
int edge[N][N];
int n, m;
int vis[N];

void backtrack (int u) { //find max independent set
   // cerr << "STACK :"; for (int v : stck) { cerr << v + 1 << " ";} cerr << '\n';
   if (stck.size() > sol.size()) {
      sol = stck;
   }

   for (int v = u; v < n; ++v) {
      bool ok = true;
      for (int s : stck) {
         if (edge[s][v]) {
            ok = false;
            break;
         }
      }
      if (ok) {
         stck.push_back(v);
         backtrack (v + 1);
         stck.pop_back();
      }
   }
}

void init() {
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) edge[i][j] = 0;
}

void solve() {
   sol.clear(), stck.clear();
   backtrack(0);

   cout << sol.size() << '\n';
   for (int i = 0; i < (int)sol.size(); ++i) {
      if (i) cout << ' ';
      cout << sol[i] + 1;
   }
   cout << '\n';
}

void read() {
   cin >> n >> m;
   init();
   for (int i = 0, u, v; i < m; ++i) {
      cin >> u >> v;
      --u, --v;
      edge[u][v] = edge[v][u] = 1;
   }
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}
