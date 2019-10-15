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

   int tc;
   cin >> tc;
   while (tc--) {
      int n;
      cin >> n;
      vector <int> w(n), dp(n), sz(n);
      vector <vector <int>> T(n, vector <int>());
      for (int i = 0; i < n; ++i) {
         cin >> w[i];
      }
      for (int e = 0; e < n - 1; ++e) {
         int u, v;
         cin >> u >> v;
         --u, --v;
         T[u].push_back(v);
         T[v].push_back(u);
      }

      function <void(int, int)> dfs
         = [&] (int u, int pr) -> void {
            for (int i = 0; i < (int)T[u].size(); ++i) if (T[u][i] == pr) {
               T[u].erase(T[u].begin() + i);
               break;
            }

            dp[u] = w[u];
            sz[u] = 1;
            for (int v : T[u]) {
               dfs(v, u);
               dp[u] += dp[v];
               sz[u] += sz[v];
            }

            sort(T[u].begin(), T[u].end(), [&] (int p, int q) {
                  return 1ll * dp[p] * (sz[q] - dp[q]) < 1ll * dp[q] * (sz[p] - dp[p]);
                  });
            // p before q if inversion keeping p ahead are less
         };

      vector <int> w_;
      function <void(int)> dfs2
         = [&] (int u) -> void {
            w_.push_back(w[u]);
            for (int v : T[u]) dfs2(v);
         };

      dfs(0, -1);
      dfs2(0);

      vector <int> suff(n);
      for (int i = n - 1; i >= 0; --i) {
         if (i == n - 1) suff[i] = (w_[i] == 0);
         else suff[i] = suff[i + 1] + (w_[i] == 0);
      }

      ll ans = 0;
      for (int i = 0; i < n; ++i) {
         if (w_[i]) ans += suff[i];
      }
      cout << ans << '\n';
   }

   return EXIT_SUCCESS;
}
