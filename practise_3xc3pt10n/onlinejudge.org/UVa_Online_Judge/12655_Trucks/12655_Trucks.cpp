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

signed main() {
   IOS; PREC;

   int n, m, s;
   while (cin >> n >> m >> s) {
      struct Edge {
         int u, v, w;
         bool operator < (const Edge& o) const {
            return w > o.w;
         }
      };
      vector <Edge> edges;
      vector <vector <pii>> T(n, vector <pii>());

      for (int e = 0; e < m; ++e) {
         int u, v, w;
         cin >> u >> v >> w;
         --u, --v;
         edges.push_back({u, v, w});
      }

      sort(edges.begin(), edges.end());
      vector <int> rep(n), rnk(n);

      auto find_set = [&] (int u) -> int {
         int x = u, temp;
         while (u != rep[u]) u = rep[u];
         while (x != rep[x]) temp = rep[x], rep[x] = u, x = temp;
         return u;
      };

      auto unite = [&] (int u, int v) -> void {
         int ru = find_set(u), rv = find_set(v);
         if (rnk[ru] > rnk[rv]) rep[rv] = ru;
         else rep[ru] = rv;
         if (rnk[rv] == rnk[ru]) ++rnk[rv];
      };

      for (int i = 0; i < n; ++i)
         rep[i] = i, rnk[i] = 1;

      for (Edge e : edges) {
         if (find_set(e.u) == find_set(e.v))
            continue;
         T[e.u].push_back(make_pair(e.v, e.w));
         T[e.v].push_back(make_pair(e.u, e.w));
         unite(e.u, e.v);
      }

      const int D = 21;
      vector <vector <int>> table(n, vector <int>(D + 1, -1));
      vector <vector <int>> dp(n, vector<int>(D + 1, INT_MAX));
      vector <int> depth(n);

      function <void(int, int, int)> dfs
         = [&] (int u, int pr, int d) {
            depth[u] = d;
            for (int k = 1; k <= D; ++k) {
               if (table[u][k - 1] != -1) {
                  table[u][k] = table[table[u][k - 1]][k - 1];
                  dp[u][k] = min(dp[u][k - 1], dp[table[u][k - 1]][k - 1]);
               }
            }
            for (auto vp : T[u]) {
               int v = vp.x, w = vp.y;
               if (v == pr) continue;
               table[v][0] = u;
               dp[v][0] = w;
               dfs(v, u, d + 1);
            }
         };

      auto walk = [&] (int &u, int k) -> int {
         int mn = INT_MAX;
         for (int d = 0; d <= D && u >= 0; ++d)
            if ((1 << d) & k) {
               mn = min(mn, dp[u][d]);
               u = table[u][d];
            }
         return mn;
      };

      auto get_min = [&] (int u, int v) -> int {
         int mn = INT_MAX;
         if (depth[u] > depth[v])
            mn = min(mn, walk(u, depth[u] - depth[v]));
         if (depth[v] > depth[u])
            mn = min(mn, walk(v, depth[v] - depth[u]));
         if (u == v) return mn;

         for (int d = D; d >= 0; --d) {
            if (table[u][d] != table[v][d]) {
               mn = min({mn, dp[u][d], dp[v][d]});
               u = table[u][d], v = table[v][d];
            }
         }
         return mn = min({mn, dp[u][0], dp[v][0]});
      };

      dfs(0, -1, 0);

      while (s--) {
         int l, h;
         cin >> l >> h;
         --l, --h;
         cout << get_min(l, h) << '\n';
      }
   }
   return EXIT_SUCCESS;
}
