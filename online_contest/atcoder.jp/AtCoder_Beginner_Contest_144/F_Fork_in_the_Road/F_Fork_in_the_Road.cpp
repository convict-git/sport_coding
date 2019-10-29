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
#define fr(i,x,y) for (int i = (int)x; i <= (int)y; ++i)
#define rv(i,x,y) for (int i = (int)x; i >= (int)y; --i)
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
using   vl  =     vector<ll>;
using   vvi =     vector <vi>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
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

   int n, m;
   cin >> n >> m;

   vvi G(n, vi());

   fr(e, 1, m) {
     int u, v;
     cin >> u >> v;
     --u, --v;
     G[u].push_back(v);
   }

   const ff inf = 1e18;
   vector <ff> dp(n, inf);

   dp[n-1] = 0;

   for (int i = n-2; i >= 0; --i) {
     ff sm = 0;
     for (int j : G[i]) sm += dp[j];
     sm /= G[i].size();
     dp[i] = 1 + sm;
   }
   ff mn = dp[0];

   for (int i = 0; i < n-1; ++i) { // O(NM)// already in topological order
     if (G[i].size() == 1) continue;
     vector <ff> new_dp(dp);

     ff local_max = -inf;
     for (int j : G[i])
       local_max = fmax(local_max, dp[j]);

     new_dp[i] = (new_dp[i] - 1) * G[i].size() - local_max;
     new_dp[i] /= (G[i].size()-1);
     new_dp[i] += 1;

     for (int j = i-1; j >= 0; --j) { // O(M)
       ff sm = 0;
       for (int k : G[j]) sm += new_dp[k];
       sm /= G[j].size();
       new_dp[j] = 1 + sm;
     }
     mn = min(mn, new_dp[0]);
   }

   cout << mn << '\n';

   return EXIT_SUCCESS;
}
