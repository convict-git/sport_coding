#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifndef CONVICTION
#pragma GCC       optimize ("Ofast")
#pragma GCC       optimize ("unroll-loops")
#pragma GCC       target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define x         first
#define y         second
#define fr(i,x,y) for (int i = x; i <= y; ++i)
#define fR(i,x,y) for (int i = x; i >= y; --i)
#define bg(x)     " [ " << #x << " : " << (x) << " ] "
#define un(x)     sort(x.begin(), x.end()), \
   x.erase(unique(x.begin(), x.end()), x.end())

using   ll  =     long long;
using   ull =     unsigned long long;
using   ff  =     long double;
using   pii =     pair<int,int>;
using   pil =     pair<int,ll>;
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

// kruskals library
// This library is created by Priyanshu Shrivastav (mr.convict)
// https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/graph.cpp
#include <bits/stdc++.h>
using namespace std;

class graph {
   public:
      /* -------------------------------------------------- */
      static const int N = (int)2e5 + 10;
      static const int inf_int = (int)1e9;
      static const long long inf_ll = (long long)1e18;

      struct Edge {
         int u, v;
         long long w;
         int id;
         inline bool operator < (const Edge &o) const {
            return w < o.w;
         }
      };

      bool IS_UNDIR, vis[N];
      int V;
      vector <vector <Edge>> adj, adj_rev;
      vector <Edge> edges;
      int deg[N];

      long long dist_s[N];
      int pi[N];

      vector <Edge> MST;

      graph (int n, bool undir = true) {
         V = n;
         adj.assign(n, vector <Edge> ());
         adj_rev.assign(n, vector <Edge> ());
         fill(dist_s, dist_s + V, inf_ll);
         fill(deg, deg + V, 0);
         IS_UNDIR = undir;
      }

      inline void add_edge (int u, int v, long long w = 1, int id = -1) {
         assert(v != u);
         adj[u].push_back({u, v, w, id});
         adj_rev[v].push_back({v, u, w, id});
         edges.push_back({u, v, w, id});
         ++deg[u];

         if (IS_UNDIR) {
            adj[v].push_back({v, u, w, id});
            adj_rev[u].push_back({u, v, w, id});
            edges.push_back({v, u, w, id});
            ++deg[v];
         }
      }

      long long kruskals () {
         assert(IS_UNDIR);
         sort(edges.begin(), edges.end());
         MST.clear();
         int rep[N], rnk[N];

         for(int u = 0; u < V; ++u)
            rep[u] = u, rnk[u] = 0;

         function <int(int)> find_set = [&] (int u) -> int {
            int ru = u;
            while (ru != rep[ru])
               ru = rep[ru];

            while (u != rep[u]) {
               int tmp = rep[u];
               rep[u] = ru;
               u = tmp;
            }
            return ru;
         };

         function <void(int, int)> merge_set = [&] (int u, int v)->void {
            int ru = find_set(u), rv = find_set(v);
            if (rnk[ru] > rnk[rv]) rep[rv] = rep[ru];
            else rep[ru] = rep[rv];

            if (rnk[ru] == rnk[rv])
               ++rnk[rv];
         };


         long long cost = 0;
         int edge_cnt_mst = 0;

         for (Edge e : edges) {
            int u = e.u, v = e.v;
            long long w = e.w;
            if (find_set(u) == find_set(v)) continue;
            cost += w;
            merge_set(u, v);
            MST.push_back(e);
            ++edge_cnt_mst;
         }

         // assert (edge_cnt_mst == V - 1);
         return cost;
      }
};

/* -------------------------------------------------------------------------- */

class LCA {
   public:
      int V;
      const int D = 21; // for handling n upto 2e6
      vector <vector <int>> table, dp;
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
         dp.assign(n, vector <int>(D + 1, INT_MIN));
         depth.assign(n, 0);

         function <void(int, int, int)> dfs =
            [&](int u, int pr, int d) -> void {
               depth[u] = d;
               for (auto v_pair : T[u]) {
                  int v = v_pair.first;
                  int w = v_pair.second;
                  if (v == pr) continue;
                  table[v][0] = u;
                  dp[v][0] = w;
                  dfs(v, u, d + 1);
               }
            };

         dfs(root, -1, 0);

         for (int k = 1; k <= D; ++k) {
            for (int i = 0; i < n; ++i) {
               if (table[i][k - 1] == -1) continue;
               table[i][k] = table[table[i][k - 1]][k - 1];
               dp[i][k] = max(dp[i][k - 1], dp[table[i][k - 1]][k - 1]);
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

      int get_max_edge (int u, int v) {
         auto walk_get_max = [&] (int &i, int k) -> int {
            int mn = INT_MIN;
            for (int d = 0; d <= D && i >= 0; ++d) {
               if ((1 << d) & k) {
                  mn = max(mn, dp[i][d]);
                  i = table[i][d];
               }
            }
            return mn;
         };

         int mn = INT_MIN;
         if (depth[u] > depth[v]) {
            mn = walk_get_max(u, depth[u] - depth[v]);
         }
         if (depth[v] > depth[u]) {
            mn = walk_get_max(v, depth[v] - depth[u]);
         }
         if (u == v) return mn;
         for (int d = D; d >= 0; --d) {
            if (table[u][d] != table[v][d]) {
               mn = max({mn, dp[u][d], dp[v][d]});
               u = table[u][d]; // updates
               v = table[v][d];
            }
         }
         mn = max({mn, dp[u][0], dp[v][0]});
         return mn;
      }
};

signed main() {
   IOS; PREC;

   int n, m;
   int new_line = 0;
   while (cin >> n >> m) {
      if (new_line) cout << '\n';
      new_line = true;
      graph G(n);
      for (int i = 0; i < m; ++i) {
         int u, v, w;
         cin >> u >> v >> w;
         --u, --v;
         G.add_edge(u, v, w);
      }
      G.kruskals();
      vector <vector <pii>> T(n, vector<pii>());

      for (auto el : G.MST) {
         T[el.u].push_back(make_pair(el.v, el.w));
         T[el.v].push_back(make_pair(el.u, el.w));
      }
      LCA solve(n, T);

      int q;
      cin >> q;
      for (int i = 0; i < q; ++i) {
         int u, v;
         cin >> u >> v;
         --u, --v;
         cout << solve.get_max_edge(u, v) << '\n';
      }
   }

   return EXIT_SUCCESS;
}
