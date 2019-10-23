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
   int n;
   while (cin >> n) {
      vector <vector <int>> uT(n, vector <int>());
      vector <int> pi(n, -1);
      for (int i = 0; i < n; ++i) {
         cin >> pi[i];
         --pi[i];
         uT[i].push_back(pi[i]);
         uT[pi[i]].push_back(i);
      }

      vector <bool> vis(n, false);
      vector <int> cc(n, -1);

      function <void(int, int)> dfs = [&] (int u, int cc_idx) -> void {
         vis[u] = true;
         cc[u] = cc_idx;
         for (int v : uT[u]) if (!vis[v]) dfs(v, cc_idx);
      };


      int cc_idx = 0;
      for (int u = 0; u < n; ++u)
         if (!vis[u]) dfs(u, cc_idx++);

      /////////////////////////////////////////////////////
      vector <int> root(cc_idx, -1);

      vis.assign(n, false);
      function <void(int, int)> dfs2 =
         [&] (int u, int pr) -> void{
            vis[u] = true;

            for (int v : uT[u]) if (v != pr) {
               if (vis[v]) root[cc[v]] = v;
               else dfs2 (v, u);
            }
         };

      for (int i = 0; i < n; ++i) {
         if (!vis[i]) dfs2(i, -1);
         if (pi[pi[i]] == i) root[cc[i]] = i;
      }

      vector <bool> take(n, false);
      for (int i = 0; i < cc_idx; ++i)
         if (root[i] != -1) take[root[i]] = true;

      vector <vector <int>> T(n + n, vector <int>());
      for (int i = 0; i < n; ++i) {
         if (!take[i]) {
            T[pi[i]].push_back(i);
            T[pi[i] + n].push_back(i + n);
         }
         else {
            T[pi[i]].push_back(i + n);
         }
      }
      /////////////////////////////////////////////////////

      const int D = 21;
      vector <vector <int>> table(n+n, vector <int>(D + 1, -1));
      vector <int> depth(n+n, 0);

      function <void(int, int)> dfs3 = [&] (int u, int d) -> void {
         depth[u] = d;
         for (int k = 1; k <= D; ++k) if (table[u][k-1] != -1) {
            table[u][k] = table[table[u][k-1]][k-1];
         }
         for (int v : T[u]) {
            table[v][0] = u;
            dfs3(v, d+1);
         }
      };

      for (int i = 0; i < cc_idx; ++i) {
         dfs3(root[i], 0);
      }

      auto walk = [&] (int u, int l) -> int {
         for (int d = 0; d <= D && u >= 0; ++d)
            if ((1 << d) & l)
               u = table[u][d];
         return u;
      };

      auto lca = [&] (int u, int v) -> int {
         if (depth[v] > depth[u]) v = walk(v, depth[v] - depth[u]);
         if (depth[u] > depth[v]) u = walk(u, depth[u] - depth[v]);
         if (u == v) return u;

         for (int d = D; d >= 0; --d) {
            if (table[u][d] == table[v][d]) continue;
            u = table[u][d], v = table[v][d];
         }
         assert(table[u][0] == table[v][0]);
         return table[u][0];
      };

      /////////////////////////////////////////////////////
      int q; cin >> q;
      while (q--) {
         int u, v;
         cin >> u >> v; --u, --v;
         if (cc[u] != cc[v]) cout << -1 << '\n';
         else {
            int mn = INT_MAX;
            int U[] = {u, u + n};
            int V[] = {v, v + n};
            for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) {
               int u_ = U[i], v_ = V[j];
               int z = lca(u_, v_);
               mn = min(mn, depth[u_] - depth[z] + depth[v_] - depth[z]);
            }
            cout << mn << '\n';
         }
      }
   }

   return EXIT_SUCCESS;
}
