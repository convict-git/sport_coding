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
   int operator()(pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

seed_seq seq{
   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
      (uint64_t) __builtin_ia32_rdtsc(),
      (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]

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

const int N = (int)1e5 + 10;
const int Mod = 998244353;
}
vector <int> fac;
vector <Mint> fac;
vector <pii> el;
inline int add(int x, int y) {
   return (x + y) % Mod;
}
inline int sub(int x, int y) {
   return (x - y + Mod) % Mod;
}
inline int mul (int x, int y) {
   return int(1ll*x*y % Mod);
}

int solve_single() {
   sort(el.begin(), el.end());
   int ans = 1;
   int cur_x = el[0].x, cnt = 1;
   for (int i = 1; i < n; ++i) {
      if (cur_x == el[i].x) {
         cnt = add(cnt, 1);
      }
      else {
         ans = mul(ans, fac[cnt]);
         cur_x = el[i].x;
         cnt = 1;
      }
   }
   ans = mul(ans, fac[cnt]);
   return ans;
}

int solve_double() {
   sort(el.begin(), el.end());
   for (int i = 1; i < n; ++i) {
      if (el[i].y < el[i - 1].y) return 0;
   }
   int ans = 1;
   int cur_x = el[0].x, cur_y = el[0].y, cnt = 1;
   for (int i = 1; i < n; ++i) {
      if (cur_x == el[i].x) {
         if (cur_y == el[i].y) {
            cnt = add(cnt, 1);
         }
         else {
            ans = mul(ans, fac[cnt]);
            cur_y = el[i].y;
            cnt = 1;
         }
      }
      else {
         ans = mul(ans, fac[cnt]);
         cur_x = el[i].x, cur_y = el[i].y;
         cnt = 1;
      }
   }
   ans = mul(ans, fac[cnt]);
   return ans;
}

void solve() {
   int a = solve_single();
   for (int i = 0; i < n; ++i) {
      swap(el[i].x, el[i].y);
   }
   int b = solve_single();
   int c = solve_double();
   cout << sub(fac[n], sub(add(a, b), c)) << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n;
   fac.push_back(1);
   for (int i = 1; i <= n; ++i) {
      fac.push_back(mul(i, fac.back()));
   }

   for (int i = 0; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      el.emplace_back(x, y);
   }
   solve();

   return EXIT_SUCCESS;
}
