#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifndef CONVICTION
#pragma GCC   optimize ("Ofast")
#pragma GCC   optimize ("unroll-loops")
#pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS   ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC  cout.precision (10); cout << fixed
#define x     first
#define y     second
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define un(x) sort(x.begin(), x.end()), \
   x.erase(unique(x.begin(), x.end()), x.end())
using   ll  = long long;
using   ull = unsigned long long;
using   ff  = long double;
using   pii = pair<int,int>;
using   pil = pair<int,ll>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
   int operator () (pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

#if __cplusplus > 201103L
seed_seq seq{
   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
      (uint64_t) __builtin_ia32_rdtsc(),
      (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]
#else
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed);
#endif

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
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong

#include      <bits/stdc++.h>
using namespace std;

class LCA {
   public:
   int V;
   const int D = 21; // for handling n upto 2e6
   vector <vector <int>> table, dp_min, dp_max;
   vector <int> depth;

   inline int walk(int u, int k) {
      for (int d = 0; d <= D && u != -1; ++d) {
         if ((1 << d) & k) {
            u = table[u][d];
         }
      }
      return u;
   }

   LCA(int n, vector <vector<pair <int, int>>> &T, int root = 0) {
      V = n;
      table.assign(n, vector <int>(D + 1, -1));
      depth.assign(n, 0);
      dp_min.assign(n, vector <int>(D + 1, INT_MAX));
      dp_max.assign(n, vector <int>(D + 1, INT_MIN));

      function <void(int, int, int)> dfs =
         [&](int u, int pr, int d) -> void {
            depth[u] = d;
            for (auto v_pair : T[u]) {
               int v = v_pair.first;
               int w = v_pair.second;
               if (v == pr) continue;
               table[v][0] = u;
               dp_min[v][0] = w;
               dp_max[v][0] = w;
               dfs(v, u, d + 1);
            }
         };

      dfs(root, -1, 0);

      for (int k = 1; k <= D; ++k) {
         for (int i = 0; i < n; ++i) {
            if (table[i][k - 1] == -1) continue;
            table[i][k] = table[table[i][k - 1]][k - 1];
            dp_min[i][k] = min(dp_min[i][k - 1], dp_min[table[i][k - 1]][k - 1]);
            dp_max[i][k] = max(dp_max[i][k - 1], dp_max[table[i][k - 1]][k - 1]);
         }
      }
   }

   int find_lca(int u, int v) {
      if (depth[u] > depth[v]) {
         u = walk(u, depth[u] - depth[v]);
      }
      else if (depth[u] < depth[v]) {
         v = walk(v, depth[v] - depth[u]);
      }
      if (u == v) return u;

      for (int d = D; d >= 0; --d) {
         if (table[u][d] != table[v][d]) {
            u = table[u][d];
            v = table[v][d];
         }
      }
      return table[u][0];
   }

   pii get_min_max_edge (int u, int v) {
      auto walk_get_min_max = [&] (int &i, int k) -> pii {
         int mn = INT_MAX, mx = INT_MIN;
         for (int d = 0; d <= D && i >= 0; ++d) {
            if ((1 << d) & k) {
               mn = min(mn, dp_min[i][d]);
               mx = max(mx, dp_max[i][d]);
               i = table[i][d];
            }
         }
         return make_pair(mn, mx);
      };

      int mn = INT_MAX, mx = INT_MIN;
      if (depth[u] > depth[v]) {
         pii temp = walk_get_min_max(u, depth[u] - depth[v]);
         mn = min(mn, temp.x), mx = max(mx, temp.y);
      }
      if (depth[v] > depth[u]) {
         pii temp = walk_get_min_max(v, depth[v] - depth[u]);
         mn = min(mn, temp.x), mx = max(mx, temp.y);
      }

      if (u == v) return make_pair(mn, mx);
      for (int d = D; d >= 0; --d) {
         if (table[u][d] != table[v][d]) {
            mn = min({mn, dp_min[u][d], dp_min[v][d]});
            mx = max({mx, dp_max[u][d], dp_max[v][d]});
            u = table[u][d]; // updates
            v = table[v][d];
         }
      }
      mn = min({mn, dp_min[u][0], dp_min[v][0]});
      mx = max({mx, dp_max[u][0], dp_max[v][0]});
      return make_pair(mn, mx);
   }
};
signed main() {
   IOS; PREC;

   int n; cin >> n;
   vector <vector <pii>> T(n, vector <pii>());
   for (int e = 0; e < n - 1; ++e) {
      int u, v, w; cin >> u >> v >> w;
      --u, --v;
      T[u].push_back(make_pair(v, w));
      T[v].push_back(make_pair(u, w));
   }
   LCA lca_solve(n, T);
   int q; cin >> q;
   while (q--) {
      int u, v; cin >> u >> v; --u, --v;
      pii temp = lca_solve.get_min_max_edge(u, v);
      assert(temp.x != INT_MAX && temp.y != INT_MIN);
      cout << temp.x << ' ' << temp.y << '\n';
   }

   return EXIT_SUCCESS;
}
