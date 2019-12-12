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
   int tc;
   cin >> tc;
   vector <ff> dp_n, dp_m;
   vp point;
   auto dist = [&] (pii p1, pii p2) -> ff {
     return hypot (p1.x - p2.x, p1.y - p2.y);
   };

   while (tc--) {
     int n, m, k, x, y;
     cin >> x >> y >> n >> m >> k;

     point.assign(n + k + m + 1, pii());
     ff inf = 1e18;
     dp_n.assign(n + m + k + 1, inf);
     dp_m.assign(n + m + k + 1, inf);

     point[0] = make_pair(x, y);

     fr(i, 1, n + 1 - 1) cin >> point[i].x >> point[i].y;
     fr(i, n + 1, n + m + 1 - 1) cin >> point[i].x >> point[i].y;
     fr(i, n + m + 1, n + m + k + 1 - 1) {
       cin >> point[i].x >> point[i].y;
       dp_m[i] = dp_n[i] = 0;
     }

     fr (i, n + 1, n + m + 1 - 1) // in m
       fr (j, n + m + 1, n + m + k + 1 - 1) // in k
         dp_n[i] = min(dp_n[i], dp_n[j] + dist(point[i], point[j]));

     fr (i, 1, n + 1 - 1) // in n
       fr (j, n + 1, n + m + 1 - 1) // in m
         dp_n[i] = min(dp_n[i], dp_n[j] + dist(point[i], point[j]));

     fr (j, 1, n + 1 - 1) // in n
       dp_n[0] = min(dp_n[0], dp_n[j] + dist(point[0], point[j]));

     fr (i, 1, n + 1 - 1) // in n
       fr (j, n + m + 1, n + m + k + 1 - 1) // in k
         dp_m[i] = min(dp_m[i], dp_m[j] + dist(point[i], point[j]));

     fr (i, n + 1, n + m + 1 - 1) // in m
       fr (j, 1, n + 1 - 1) // in n
         dp_m[i] = min(dp_m[i], dp_m[j] + dist(point[i], point[j]));

     fr (j, n + 1, n + m + 1 - 1) // in n
       dp_m[0] = min(dp_m[0], dp_m[j] + dist(point[0], point[j]));

     cout << min(dp_n[0], dp_m[0]) << '\n';
   }
   return EXIT_SUCCESS;
}
