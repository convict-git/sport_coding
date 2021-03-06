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

signed main() {
   IOS; PREC;

   int n, q;
   cin >> n >> q;
   vvi T(n, vi());
   for (int i = 1; i < n; ++i) {
      int p; cin >> p; --p;
      T[p].push_back(i);
   }
   const int D = 21;
   vi depth(n, 0);
   vvi table(n, vi(D+1,-1));

   function <void(int, int)> dfs = [&]
      (int u, int d) {
         depth[u] = d;
         for (int k = 1; k <= D; ++k) if (table[u][k-1] != -1)
            table[u][k] = table[table[u][k-1]][k-1];

         for (int v : T[u]) {
            table[v][0] = u;
            dfs(v, d+1);
         }
      };
   dfs(0, 0);

   auto find_lca = [&] (int u, int v) -> int {
      auto walk = [&] (int i, int l) -> int {
         for (int d = 0; d <= D && i >= 0; ++d)
            if ((1 << d) & l) i = table[i][d];
         return i;
      };
      if (depth[u] > depth[v]) u = walk(u, depth[u] - depth[v]);
      if (depth[v] > depth[u]) v = walk(v, depth[v] - depth[u]);
      if (u == v) return u;
      for (int d = D; d >= 0; --d) if (table[u][d] != table[v][d])
         u = table[u][d], v = table[v][d];
      return table[u][0];
   };

   auto solve = [&] (int s, int t, int f) -> int {
      // assuming f as root find z as the new lca of s and t
      // return dist(z, f)
      int st = find_lca(s, t);
      int sf = find_lca(s, f);
      int tf = find_lca(t, f);

      int z = -1;
      if (sf == tf) z = st;
      else if (sf == st) z = tf;
      else if (tf == st) z = sf;
      else assert(false);

      int foo = find_lca(z, f);
      return depth[z] - depth[foo] + depth[f] - depth[foo] + 1;
   };

   while (q--) {
      vi inp(3);
      fr(i, 0, 2) cin >> inp[i], --inp[i];
      int mx = 0;
      mx = max({mx,
            solve(inp[0], inp[1], inp[2]),
            solve(inp[1], inp[2], inp[0]),
            solve(inp[2], inp[0], inp[1])});
      cout << mx << '\n';
   }

   return EXIT_SUCCESS;
}
