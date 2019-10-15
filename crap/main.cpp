#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#pragma GCC   optimize ("Ofast")
#pragma GCC   optimize ("unroll-loops")
#pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS   ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC  cout.precision (10); cout << fixed
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define x     first
#define y     second
using   ll  = long long;
using   ull = unsigned long long;
using   ff  = long double;
using   pii = pair<int,int>;
using   pil = pair<int,ll>;

typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
   int operator()(pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed); //uniform_int_distribution<T> (l, h)(rng); //[low, high]

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

string s, t, p;

void solve() {
   cin >> s >> t >> p;
   sort (p.begin(), p.end());
   if (s.size() > t.size()) {
      cout << "NO\n";
   }
   else {
      bool ok = true;
      int len = (int)t.size();
      for (int i = 0, j = 0; i < len && ok; ++i, ++j) {
         if (s[j] != t[i]) {
            bool found = false;
            char miss = t[i];
            int l = 0, h = (int)p.size() - 1;
            while (l <= h) {
               int g = (l + h)/2;
               if (p[g] == miss) {
                  --j;
                  p.erase(p.begin() + g);
                  found = true;
                  break;
               }
               else if (p[g] < miss) {
                  l = g + 1;
               }
               else h = g - 1;
            }
            if (!found) ok = false;
         }
      }
      if (ok) cout << "YES\n";
      else cout << "NO\n";
   }
}
signed main() {
   int q;
   cin >> q;
   while (q--) {
      solve();
   }

   return EXIT_SUCCESS;
}

