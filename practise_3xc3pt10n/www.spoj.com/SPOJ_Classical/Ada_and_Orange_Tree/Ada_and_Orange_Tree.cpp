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
   int tc;
   cin >> tc;
   while (tc--) {

      int n; cin >> n;
      int q, root; cin >> q >> root;

      vector <vector <int>> T(n, vector <int>());
      vector <int> val(n);

      for (int i = 0; i < n; ++i)
         cin >> val[i];

      for (int i = 0; i < n - 1; ++i) {
         int u, v;
         cin >> u >> v;
         T[u].push_back(v);
         T[v].push_back(u);
      }

      struct Set {
         bool b[251] = {0};
         void reset() {
            for (int i = 0; i < 251; ++i)
               b[i] = false;
         }
         void unite(Set s2) {
            for (int i = 0; i < 251; ++i)
               b[i] = b[i] | s2.b[i];
         }
         int count () {
            int cnt = 0;
            for (int i = 0; i < 251; ++i)
               cnt += b[i];
            return cnt;
         }
      };


      vector <Set> shades(n);
      const int D = 21;
      vector <int> depth(n, 0);
      vector <vector <int>> table(n, vector <int> (D + 1, -1));

      function <void(int, int, int)> dfs
         = [&] (int u, int pr, int d) {
            depth[u] = d;
            shades[u].b[val[u]] = true;

            for (int k = 1; k <= D; ++k) {
               if (table[u][k - 1] != -1)
                  table[u][k] = table[table[u][k - 1]][k - 1];
            }

            for (int v : T[u]) {
               if (v == pr) continue;
               table[v][0] = u;
               dfs(v, u, d + 1);
               shades[u].unite(shades[v]);
            }
         };

      auto walk = [&] (int u, int k) -> int {
         for (int d = 0; d <= D && u >= 0; ++d) {
            if ((1 << d) & k)
               u = table[u][d];
         }
         return u;
      };

      auto lca = [&] (int u, int v) -> int {
         if (depth[u] > depth[v])
            u = walk(u, depth[u] - depth[v]);
         if (depth[v] > depth[u])
            v = walk(v, depth[v] - depth[u]);
         if (u == v) return u;

         for (int d = D; d >= 0; --d) {
            if (table[u][d] != table[v][d])
               u = table[u][d], v = table[v][d];
         }
         return table[u][0];
      };

      dfs(root, -1, 0);

      while (q--) {
         int u, v;
         cin >> u >> v;
         cout << shades[lca(u, v)].count() << '\n';
      }
   }
   return EXIT_SUCCESS;
}
