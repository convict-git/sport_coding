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

   int n;
   while (cin >> n, n) {
      const int D = 21;
      vector <vector <pii>> T(n, vector <pii>());
      vector <vector <int> > table(n, vector <int> (D + 1, -1));
      vector <vector <int>> dp(n, vector <int>(D + 1, INT_MIN));
      vector <int> depth(n, 0);
      for (int i = 0; i < n - 1; ++i) {
         int u, v, w;
         cin >> u >> v >> w;
         --u, --v;
         T[u].push_back(make_pair(v, w));
         T[v].push_back(make_pair(u, w));
      }

      function <void(int, int, int)> dfs =
         [&] (int u, int pr, int d) {
            depth[u] = d;
            for (int k = 1; k <= D; ++k) if (table[u][k-1] != -1) {
               table[u][k] = table[table[u][k-1]][k-1];
               dp[u][k] = max(dp[table[u][k-1]][k-1], dp[u][k-1]);
            }

            for (auto vp : T[u]) if (vp.x != pr) {
               table[vp.x][0] = u;
               dp[vp.x][0] = vp.y;
               dfs(vp.x, u, d+1);
            }
         };

      dfs(0, -1, 0);

      auto walk_get_max = [&] (int& u, int k) {
         int mx = INT_MIN;
         for (int d = 0; d <= D && u >= 0; ++d) if ((1 << d) & k) {
            mx = max(mx, dp[u][d]);
            u = table[u][d];
         }
         return mx;
      };

      auto get_max = [&] (int u, int v) {
         int mx = INT_MIN;
         if (depth[u] > depth[v]) mx = max(mx, walk_get_max(u, depth[u] - depth[v]));
         if (depth[v] > depth[u]) mx = max(mx, walk_get_max(v, depth[v] - depth[u]));
         if (u == v) return mx;

         for (int d = D; d >= 0; --d) if (table[u][d] != table[v][d]) {
            mx = max({mx, dp[u][d], dp[v][d]});
            u = table[u][d], v = table[v][d];
         }
         return mx = max({mx, dp[u][0], dp[v][0]});
      };
      int q;
      cin >> q;
      while (q--) {
         int u, v;
         cin >> u >> v;
         --u, --v;
         cout << get_max(u, v) << '\n';;
      }
      cout << '\n';
   }

   return EXIT_SUCCESS;
}
