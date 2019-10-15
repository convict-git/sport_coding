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

   int n, m;
   cin >> n >> m;
   vector <set<int>> adj(n, set<int>());
   set <int> color[3];
   vector <int> deg(n);
   vector <int> colored(n, -1);
   bool ok = true;

   for (int e = 0; e < m; ++e) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      adj[u].insert(v);
      adj[v].insert(u);
      ++deg[u], ++deg[v];
   }

   color[0].insert(0);
   colored[0] = 0;
   for (int u = 0; u < n; ++u) { // color white for 1st group
      if (u == 0 || adj[0].find(u) != adj[0].end()) {
         continue;
      }
      color[0].insert(u); // white
      colored[u] = 0;
   }

   for (int u : color[0]) { // color black for second group
      if (!ok) break;
      if (deg[u]) { // non - zero degree
         int v_ = *adj[u].begin();
         if (color[0].find(v_) != color[0].end()) {
            ok = false;
            break;
         }
         color[1].insert(v_); // black
         colored[v_] = 1;
         for (int v = 0; v < n; ++v) {
            if (v == v_ || adj[v_].find(v) != adj[v_].end()) {
               continue;
            }
            if (color[0].find(v) != color[0].end()) { // already colored white
               ok = false;
               break;
            }
            color[1].insert(v); // color black
            colored[v] = 1;
         }
         break;
      }
   }

   if (color[1].empty()) {
      ok = false;
   }

   if (ok) {
      for (int u = 0; u < n; ++u) {
         if (colored[u] == -1) { // color remaining as grey
            color[2].insert(u);
            colored[u] = 2;
         }
      }
   }

   int cnt0 = (int)color[0].size();
   int cnt1 = (int)color[1].size();
   int cnt2 = (int)color[2].size();
   int cnt[] = {cnt1 + cnt2, cnt0 + cnt2, cnt0 + cnt1};
   ok = ok && cnt0 > 0 && cnt1 > 0 && cnt2 > 0;

   for (int i = 0; ok && i < 3; ++i) {
      for (int u : color[i]) {
         if (!ok) break;
         if (deg[u] != cnt[i]) {
            ok = false;
            break;
         }
         for (int v : adj[u]) {
            if (color[i].find(v) != color[i].end()) {
               ok = false;
               break;
            }
         }
      }
   }

   if (ok) {
      for (int u = 0; u < n; ++u) {
         cout << colored[u] + 1 << ' ';
      }
      cout << '\n';
   }
   else {
      cout << -1 << '\n';
   }
   return EXIT_SUCCESS;
}
