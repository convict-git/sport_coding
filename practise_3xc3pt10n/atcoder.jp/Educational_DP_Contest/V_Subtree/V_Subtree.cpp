#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#pragma GCC   optimize ("Ofast")
#pragma GCC   optimize ("unroll-loops")
#pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS   ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC  cout.precision (10); cout << fixed
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define x     first
#define y     second
using   ll  = long long;
using   ff  = long double;
using   pii = pair<int,int>;
using   pil = pair<int,ll>;

typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
   int operator()(pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

#define debug(args...) { \
   /* WARNING : do NOT compile this debug func calls with following flags: // \
    * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); \
   istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) {
   it->empty(); cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
   cerr << fixed << setprecision(15)
      << " [ " <<  *it << " : " << a  << " ] "<< ' ';
   err(++it, args...);
}

// I messed up with the recursion which costed me extra 50 mins.
// First root the tree at some vertex (let say 0)
// lets define f[u] := no. of ways we can color the subtree of u with black
// such that u is colored black
// g[u] := no. of ways we can color the tree such that the we always color u
// and no other vertex from subtree of u is colored
//
// We need to calc f values in post order
// f[u] = (1 + f[v1])*(1 + f[v2])*....*(1 + f[vn])
// Why ? either you color the child or not
//
// and g values in preorder
// g[vi] = 1 + (pref[i-1]*suff[i+1]*g[u])
// Why ? either you color the parent or not
//
// pref[i] = (1 + f[v1])*(1 + f[v2])*....*(1 + f[vi])
// suff[i] = (1 + f[vi])*(1 + f[vi+1])*....*(1 + f[vn])
// where v1, v2, .. vn are childs of u
// base case f[leave] = 1, g[root] = 1

const int N = (int)1e5 + 10;
int n, m;
vector <vector <int>> adj;
vector <bool> vis;
vector <int> post_order, pre_order;
int f[N], g[N];
int pref[N], suff[N];

int mul(int a, int b) {
   return int(1ll*a*b % m);
}
int add(int a, int b) {
   return (a + b)%m;
}

void dfs(int u, int pr) {
   vis[u] = true;
   pre_order.push_back(u);
   for (vector <int>::iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
      int v = *it;
      if (v == pr) {
         adj[u].erase(it);
         break;
      }
   }
   for (int v : adj[u])
      if (!vis[v]) dfs(v, u);
   post_order.push_back(u);
}

void solve() {
   vis.assign(n, false);
   dfs(0, -1);

   for (int u : post_order) {
      f[u] = 1;
      for (int v : adj[u])
         f[u] = mul(f[u], add(1, f[v]));
   }

   for (int u : pre_order) {
      if (u == 0) g[u] = 1;

      int sz = (int)adj[u].size();
      for (int i = 0; i < sz; ++i) {
         int vp = adj[u][i];
         int vs = adj[u][sz - 1 - i];

         if (i == 0) {
            pref[i] = add(1, f[vp]);
            suff[sz - 1 - i] = add(1, f[vs]);
         }
         else {
            pref[i] = mul(pref[i - 1], add(1, f[vp]));
            suff[sz - 1 - i] = mul(suff[sz - 1 - i + 1], add(1, f[vs]));
         }
      }

      for (int i = 0; i < (int)adj[u].size(); ++i) {
         int v = adj[u][i];
         int down = 1;
         if (i)
            down = mul(down, pref[i-1]);
         if (i != (int)adj[u].size() - 1)
            down = mul(down, suff[i+1]);

         g[v] = add(1, mul(down, g[u]));
      }
   }

   for (int i = 0; i < n; ++i) {
      cout << mul(f[i], g[i]) << '\n';
   }
}

void read() {
   cin >> n >> m;
   adj.assign(n, vector <int>());
   for (int i = 0; i < n - 1; ++i) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      adj[u].emplace_back(v);
      adj[v].emplace_back(u);
   }
}

signed main() {
   IOS; PREC;
   read(), solve();

   return EXIT_SUCCESS;
}
