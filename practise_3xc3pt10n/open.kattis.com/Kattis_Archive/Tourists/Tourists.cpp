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

signed main() {
   IOS; PREC;

   int n;
   cin >> n;
   const int D = 18;
   vector <vector <int>> T(n, vector <int>());
   vector <vector <int>> table(n, vector <int>(D + 1, -1));
   vector <int> depth(n, 0);

   for (int e = 0; e < n - 1; ++e) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      T[u].push_back(v);
      T[v].push_back(u);
   }

   function <void(int, int, int)> dfs =
      [&] (int u, int pr, int d) -> void {
         depth[u] = d;
         for (int v : T[u]) {
            if (v == pr) continue;
            table[v][0] = u;
            dfs(v, u, d + 1);
         }
      };

   dfs (0, -1, 0);

   for (int k = 1; k <= D; ++k) {
      for (int i = 1; i < n; ++i)  {
         if (table[i][k - 1] != -1)
            table[i][k] = table[table[i][k - 1]][k - 1];
      }
   }

   auto walk = [&] (int u, int k) -> int {
      for (int d = 0; d <= D && u != -1; ++d) {
         if ((1 << d) & k)  {
            u = table[u][d];
         }
      }- CYK Algorithm

[ ] - Pumping Lemma for CFG

	( ) - Examples and proof

	( ) - Problems
      return u;
   };

   auto lca = [&] (int u, int v) {
      if (depth[u] > depth[v]) {
         u = walk(u, depth[u] - depth[v]);
      }
      if (depth[v] > depth[u]) {
         v = walk(v, depth[v] - depth[u]);
      }

      if (u == v) return u;

      for (int d = D; d >= 0; --d){
         if (table[u][d] != table[v][d]) {
            u = table[u][d];
            v = table[v][d];
         }
      }
      return table[u][0]; // jump once more
   };

   ll ans = 0;

   for (int x = 1; x <= n; ++x) { // NlogN
      for (int y = 2 * x; y <= n; y += x) {
         int z = lca(x - 1, y - 1) + 1;
         ans += depth[x - 1] + depth[y - 1] - 2 * depth[z - 1] + 1;
      }
   }
   cout << ans << '\n';

   return EXIT_SUCCESS;
}
