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
   int n;
   cin >> n;
   vvi T(n, vi());
   vp pi(n, {-1, -1});

   for (int i = 0; i < n; ++i) {
      int u, t;
      cin >> u >> t;
      if (u != -1) --u;
      pi[i].x = u;
      pi[i].y = t;
      if (pi[i].x != -1) {
         T[pi[i].x].push_back(i);
      }
   }

   const int D = 21;
   vi cc(n, -1), depth(n, 0);
   vvi table(n, vi(D+1, -1));
   vvi Sdp(n, vi(D+1, false)), Pdp(n, vi(D+1, false));

   function <void(int, int, int)> dfs = [&] (int u, int d, int cc_idx) -> void {
      cc[u] = cc_idx;
      depth[u] = d;

      for (int k = 1; k <= D; ++k) if (table[u][k-1] != -1) {
         table[u][k] = table[table[u][k-1]][k-1];
         Sdp[u][k] = Sdp[u][k-1] & Sdp[table[u][k-1]][k-1];
         Pdp[u][k] = Pdp[u][k-1] & Pdp[table[u][k-1]][k-1];
      }

      for (int v : T[u]) {
         table[v][0] = u;
         if (pi[v].y == 0) Sdp[v][0] = true;
         else if (pi[v].y == 1) Pdp[v][0] = true;
         dfs(v, d + 1, cc_idx);
      }
   };

   for (int i = 0, cc_idx = 0; i < n; ++i) if (pi[i].x == -1) {
      dfs(i, 0, cc_idx++);
   }

   auto walk = [&] (int u, int l, bool &pok, bool &sok) -> int {
      sok = pok = true;
      for (int d = 0; d <= D && u >= 0; ++d)
         if ((1 << d) & l)  {
            pok &= Pdp[u][d], sok &= Sdp[u][d];
            u = table[u][d];
         }
      return u;
   };

   auto give_lca = [&] (int u, int v) -> int {
      bool tmp1, tmp2;
      if (depth[v] > depth[u]) v = walk(v, depth[v] - depth[u], tmp1, tmp2);
      if (depth[u] > depth[v]) u = walk(u, depth[u] - depth[v], tmp1, tmp2);
      if (u == v) return u;

      for (int d = D; d >= 0; --d) {
         if (table[u][d] == table[v][d]) continue;
         u = table[u][d], v = table[v][d];
      }
      return table[u][0];
   };

   int q;
   cin >> q;
   while (q--) {
      int u, v, t;
      cin >> t >> u >> v;
      --u, --v;
      if (cc[u] != cc[v] || u == v) cout << "NO\n";
      else {
         int z = give_lca(u, v);
         if (t == 1) {
            if (u != z || depth[v] <= depth[u]) cout << "NO\n";
            else {
               bool tmp, ok;
               walk(v, depth[v] - depth[z], tmp, ok);
               if (u == z && ok) cout << "YES\n";
               else cout << "NO\n";
            }
         }
         else {
            if (z == v && depth[v] <= depth[u]) cout << "NO\n";
            else {
              bool pok = true, sok = true, tmp1, tmp2;
              walk(v, depth[v] - depth[z], pok, tmp2);
              walk(u, depth[u] - depth[z], tmp1, sok);
              if (pok && sok) cout << "YES\n";
              else cout << "NO\n";
            }
         }
      }
   }

   return EXIT_SUCCESS;
}
