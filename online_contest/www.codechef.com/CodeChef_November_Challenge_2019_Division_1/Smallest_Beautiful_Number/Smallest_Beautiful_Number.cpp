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

const int N = (int)1e5;
int dp_digit[81*N + 1], dp_len[81*N + 1];
int pi[81*N + 1];

pii rec (int i) {
  if (i >= 81 * N + 1) {
    int dig = 10;
    int len = INT_MAX;
    for (int j = 1; j < 10; ++j) {
      pii p = rec (i - j*j);
      int x = p.x, y = p.y;
      if (len > p.x || (len == p.x + 1 && dig > p.y)) {
        dig = min(dig, p.y);
        len = min(len, p.x);
      }
    }
    return make_pair(len, dig);
  }
  else return make_pair(dp_len[i], dp_digit[i]);
}

signed main() {
   IOS; PREC;

   dp_digit[0] = 10;
   dp_len[0] = 0;

   for (int i = 1; i < 81 * N + 1; ++i) {
     dp_len[i] = INT_MAX;
     dp_digit[i] = 10;

     for (int j = 1; j < 10; ++j) {
       if (i - j*j >= 0) {
         // debug(i, i - j*j);
         if (dp_len[i] > dp_len[i - j*j] + 1 || (dp_len[i] == dp_len[i - j*j] + 1 && dp_digit[i] >= j)) {
           dp_len[i] = dp_len[i - j*j] + 1;
           dp_digit[i] = min(dp_digit[i], j);
           pi[i] = j;
         }
       }
     }
   }

   for (int i = 1; 1ll * i * i <= 81 * N + 1; ++i) {
   }

   // 2500 - perfect squares

   /*
   int tc;
   cin >> tc;
   while (tc--) {
     int n;
     cin >> n;

   }
   */

   return EXIT_SUCCESS;
}
