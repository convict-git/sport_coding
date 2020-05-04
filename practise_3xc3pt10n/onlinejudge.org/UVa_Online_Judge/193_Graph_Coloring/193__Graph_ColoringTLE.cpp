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
vector <int> black, cur_solution;
vector <vector <int>> adj;
bool vis[N];
int mx_sz;
int n, m;

void backtrack(int u, int color) {
   // cerr << "STACK : "; for (int v : black) { cerr << v + 1 << ' ';} cerr << "\n";
   if ((int)black.size() > mx_sz) {
      cur_solution = black;
      mx_sz = (int)black.size();
   }

   for (int v : adj[u]) {
      if (!vis[v]) {
         // if u is white send with both colors else send with one color
         vis[v] = true;
         if (color ^ 1) black.push_back(v);
         backtrack(v, color ^ 1);
         if (color ^ 1) black.pop_back();
         vis[v] = false;

         if (!color) {
            vis[v] = true;
            backtrack(v, color);
            vis[v] = false;
         }
      }
   }
}

void solve() {
   for (int i = 0; i < n; ++i) vis[i] = false;
   mx_sz = INT_MIN;
   black.clear(), cur_solution.clear();

   vis[0] = true;
   black.push_back(0);
   backtrack(0, 1);
   black.pop_back();
   vis[0] = false;

   vis[0] = true;
   backtrack(0, 0);
   vis[0] = false;

   cout << cur_solution.size() << '\n';
   for (int i = 0; i < (int)cur_solution.size(); ++i) {
      if (i) cout << ' ';
      cout << cur_solution[i] + 1;
   } cout << '\n';
}

void init () {
   for (int i = 0; i < n; ++i) vis[i] = false;
   adj.assign(n, vector <int>());
}

void read() {
   cin >> n >> m;
   init();
   for (int i = 0, u, v; i < m; ++i) {
      cin >> u >> v;
      --u, --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

