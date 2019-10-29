#include      <bits/stdc++.h> /*{{{*/
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
#define cnt(x)    __builtin_popcount(x)
#define cntll(x)  __builtin_popcountll(x)
#define bg(x)     " [ " << #x << " : " << (x) << " ] "
#define un(x)     sort(x.begin(), x.end()), \
                  x.erase(unique(x.begin(), x.end()), x.end())
using   ll  =     long long;
using   ull =     unsigned long long;
using   ff  =     long double;
using   pii =     pair<int,int>;
using   pil =     pair<int,ll>;
using   vi  =     vector <int>;
using   vvi =     vector <vi>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
using   vl  =     vector<ll>;
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
/*}}}*/
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong

#include      <bits/stdc++.h>
using namespace std;

class LCA { /*{{{*/
   // LCA library using binary lifting + dp using binary lifting
   // This library is created by Priyanshu Shrivastav (mr.convict)
   // https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/lca_bin.cpp
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
      dp.assign(n, vector <int>(D + 1, 0));
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
            dp[i][k] = dp[table[i][k - 1]][k - 1] + dp[i][k-1];
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

   int get_sum (int u, int v) {
      auto walk_sum = [&] (int &i, int k) -> int {
         int sm = 0;
         for (int d = 0; d <= D && i >= 0; ++d) {
            if ((1 << d) & k) {
               sm += dp[i][d];
               i = table[i][d];
            }
         }
         return sm;
      };

      int sm = 0;
      if (depth[u] > depth[v]) {
         sm = walk_sum(u, depth[u] - depth[v]);
      }
      if (depth[v] > depth[u]) {
         sm = walk_sum(v, depth[v] - depth[u]);
      }
      if (u == v) return sm;
      for (int d = D; d >= 0; --d) {
         if (table[u][d] != table[v][d]) {
            sm += dp[u][d] + dp[v][d];
            u = table[u][d]; // updates
            v = table[v][d];
         }
      }
      sm += dp[u][0] + dp[v][0];
      return sm;
   }
}; /*}}}*/

signed main() {
   IOS; PREC;

   int tc;
   cin >> tc;
   while (tc--){
      int n, q;
      cin >> n >> q;
      vvp T(n, vp());
      for (int i = 0; i < n-1; ++i) {
         int u, v;
         cin >> u >> v;
         --u, --v;
         T[u].push_back(make_pair(v, 1));
         T[v].push_back(make_pair(u, 1));
      }

      LCA lca_solve(n, T);
      while (q--) {
         int a, b, da, db;
         cin >> a >> da >> b >> db;
         --a, --b;
         bool ok = false;
         for (int i = 0; i < n; ++i) {
            if (lca_solve.get_sum(a, i) == da && lca_solve.get_sum(b, i) == db) {
               cout << i + 1 << '\n';
               ok = true;
               break;
            }
         }
         if (!ok) cout << -1 << '\n';
      }

   }

   return EXIT_SUCCESS;
}