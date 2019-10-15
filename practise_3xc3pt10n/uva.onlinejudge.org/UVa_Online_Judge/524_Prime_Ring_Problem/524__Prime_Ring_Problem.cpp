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
const int N = 17;
int n;
int Par[N];
bool vis[N];
vector < vector <int> > adj, solutions;
vector <int> stck;

void dfs (int u, int level) {
   if (level == n - 1) {
      for (int v : adj[u]) {
         if (v != 1) continue;
         vector <int> sol;
         while (true) {
            sol.push_back(u);
            if (u == 1) break;
            u = Par[u];
         }
         reverse(sol.begin(), sol.end());
         solutions.push_back(sol);
      }
      return;
   }
   vis[u] = true;
   for (int v : adj[u]) {
      if (!vis[v]) {
         Par[v] = u;
         stck.push_back(v);
         dfs(v, level + 1);
         stck.pop_back();
      }
   }
   vis[u] = false;
}

bool is_prime(int p) {
   for (int d = 2; d * d <= p; ++d) {
      if (!(p % d)) return false;
   }
   return true;
}

void init() {
   adj.assign(n + 1, vector <int> ());
   solutions.clear();
}

void solve(int tc) {
   init();
   cout << "Case " << tc << ":\n";
   for (int i = 1; i <= n; i += 2) {
      for (int j = 2; j <= n; j += 2) {
         if (is_prime(i + j)) {
            adj[i].push_back(j);
            adj[j].push_back(i);
         }
      }
   }
   dfs (1, 0);
   for (auto sol : solutions) {
      for (int i = 0; i < (int)sol.size(); ++i) {
         cout << sol[i] << " \n"[i == (int)sol.size() - 1];
      }
   }
}

signed main() {
   IOS; PREC;
   int tc = 0;
   while(cin >> n) {
      if (tc) cout << '\n';
      solve(++tc);
   }

   return EXIT_SUCCESS;
}

