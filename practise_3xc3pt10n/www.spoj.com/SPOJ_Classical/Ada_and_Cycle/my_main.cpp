/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */
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

const int N = 2004;
const int infi = (int)1e9;
int n;
vector <vector <int>> adj, adj_t, adjcc;
vector <int> order;
bool vis[N];
int cc[N], cc_idx = 0;

void dfs_order(const int &u) {
   vis[u] = true;
   for (int v : adj[u]) if(!vis[v]) dfs_order(v);
   order.push_back(u);
}

void dfs_cc(const int &u) {
   vis[u] = true;
   cc[u] = cc_idx;
   for (int v : adj_t[u]) if (!vis[v]) dfs_cc(v);
}

int bfs(int s) {
   queue <int> q;
   vector <int> dist(n, infi);
   vector <bool> used(n, false);

   q.push(s);
   dist[s] = 0;

   while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (int v : adjcc[u]) {
         if (!used[v]) {
            dist[v] = dist[u] + 1;
            used[v] = true;
            q.push(v);
         }
         if (v == s) return dist[s];
      }
   }
   return -1;
}

signed main() {
   IOS; PREC;

   cin >> n;
   adj.assign(n, vector <int> ());
   adjcc.assign(n, vector <int> ());
   adj_t.assign(n, vector <int> ());
   order.clear();
   cc_idx = 0;

   int tmp;
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
         cin >> tmp;
         if(tmp){
            adj[i].push_back(j);
            adj_t[j].push_back(i);
         }
      }
   }

   for (int i = 0; i < n; ++i)vis[i] = false;
   for (int i = 0; i < n; ++i)
      if (!vis[i]) dfs_order(i);
   assert(order.size());
   reverse(order.begin(), order.end());

   for (int i = 0; i < n; ++i)vis[i] = false, cc[i] = -1;
   for (int u : order) {
      if (!vis[u]) dfs_cc(u), ++cc_idx;
   }

   for (int u : order) {
      for (int v : adj[u]) {
         if (cc[u] == cc[v]) {
            adjcc[u].push_back(v);
         }
      }
   }

   for (int i = 0; i < n; ++i) {
      int ans = bfs(i);
      if (ans != -1) cout << ans << '\n';
      else cout << "NO WAY\n";
   }

   return EXIT_SUCCESS;
}



