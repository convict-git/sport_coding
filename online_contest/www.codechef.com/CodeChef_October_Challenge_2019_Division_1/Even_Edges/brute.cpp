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
      int n, m;
      cin >> n >> m;

      vector <vector <int>> G(n, vector <int>());
      for (int i = 0; i < m; ++i) {
         int u, v;
         cin >> u >> v;
         --u, --v;
         G[u].push_back(v);
         G[v].push_back(u);
      }

      bool ok = false;
      int cnt1 = 0;
      for (int i = 0; i < n; ++i)
         cnt1 += (int)G[i].size();

      if (cnt1 % 2 == 0) { // check if k can be 1
         cnt1 /= 2;
         if (cnt1 % 2 == 0) {
            cout << "Possible with 1\n";
            ok = true;
         }
      }

      for (int mask = 0;!ok &&  mask < (1 << n); ++mask) { // check if k can be 2
         int ec1 = 0, ec2 = 0;
         for (int j = 0; j < n; ++j) {
            if ((1 << j) & mask) {
               for (int i : G[j]) {
                  if ((1 << i) & mask) ++ec1;
               }
            }
            else {
               for (int i : G[j])
                  if (!((1 << i) & mask)) ++ec2;
            }
         }
         assert(ec1 % 2 == 0 && ec2 % 2 == 0);
         ec1 /= 2, ec2 /= 2;
         if (ec1 % 2 == 0 && ec2 % 2 == 0) {
            for (int i = 0; i < n; ++i)
               cout << (((1 << i) & mask )!= 0) + 1 << ' ';
            cout << '\n';
            cout << "Possible with 2\n";
            ok = true;
            break;
         }
      }

      if (!ok) cout << "I give up! k is more than 2. I'm dumb.\n";
   }


   return EXIT_SUCCESS;
}

