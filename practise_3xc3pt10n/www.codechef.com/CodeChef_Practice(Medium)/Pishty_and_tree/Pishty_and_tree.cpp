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
   int tc; cin >> tc;

   while (tc--) {
      int n; cin >> n;
      vector <vector <pii>> T(n, vector <pii> ());

      struct Edge {
         int u, v, w, idx;
         bool operator < (const Edge& o) const  {
            return w < o.w;
         }
      };
      vector <Edge> edges;

      for (int e = 0; e < n - 1; ++e) {
         int u, v, w;
         cin >> u >> v >> w;
         --u, --v;
         T[u].push_back(make_pair(v, w));
         T[v].push_back(make_pair(u, w));
         edges.push_back({u, v, w, -1});
      }

      vector <Edge> queries;
      int q; cin >> q;
      for (int i = 0; i < q; ++i) {
         int u, v, k;
         cin >> u >> v >> k;
         --u, --v;
         queries.push_back({u, v, k, i});
      }
      sort (edges.begin(), edges.end());
      sort (queries.begin(), queries.end());

      vector <int> pi(n, -1), entry(n), xit(n);
      vector <int> euler;

      function <void(int, int)> dfs =
         [&] (int u, int pr) -> void {
            pi[u] = pr;
            euler.push_back(u);
            entry[u] = (int)euler.size();

            for (auto vp : T[u]) {
               int v = vp.x;
               if (v == pr) continue;
               dfs(v, u);
            }
            euler.push_back(u);
            xit[u] = (int)euler.size();
         };

      dfs(0, -1); // find euler tour

      for (Edge &e : edges) if (pi[e.u] == e.v)
            swap(e.u, e.v);

      // fenwick tree on euler tour
      int sz = (int)euler.size();
      vector <int> BIT(sz + 2);
      auto update = [&] (int x, int val) -> void {
         while (x <= sz)
            BIT[x] ^= val, x += (x & -x);
      };
      auto get_xor = [&] (int x) -> int {
         int xr_val = 0;
         while (x > 0)
            xr_val ^= BIT[x], x -= (x & -x);
         return xr_val;
      };

      vector <int> answer(q);
      int epr = 0;
      for (auto qr : queries) {
         while (epr < n - 1 && edges[epr].w <= qr.w) {
            int l = entry[edges[epr].v];
            int h = xit[edges[epr].v];

            update (l, edges[epr].w);
            update (h + 1, edges[epr].w);
            ++epr;
         }

         int xru = get_xor (entry[qr.u]);
         int xrv = get_xor (entry[qr.v]);
         answer[qr.idx] = xru ^ xrv;
      }

      for (int el : answer) cout << el << '\n';
   }


   return EXIT_SUCCESS;
}
