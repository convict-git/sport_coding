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

const int Mod = (int)1e9 + 7;
const int N = (int)1e5 + 5;

inline int add (int x, int y) {
   return (x + y) % Mod;
}
inline int mul (int x, int y) {
   return (int)(1ll * x * y % Mod);
}
inline int sub (int x, int y) {
   return (x - y + Mod) % Mod;
}

int dp_cur[10][2], dp_prv[10][2];
int cnt_cur[10], cnt_prv[10];

vector <int> pw10;

int solve(const string &s, bool take_last = true) {
   int sz = (int)s.size();
   while ((int)pw10.size() <= sz) {
      pw10.push_back(mul(pw10.back(), 10));
   }

   for (int d = 0; d <= 9; ++d) {
      cnt_cur[d] = cnt_prv[d] = 0;
      for (bool last : {false, true}) {
         dp_cur[d][last] = dp_prv[d][last] = 0;
      }
   }

   int fch = int(s[0] - '0'), lch = int(s[sz - 1] - '0');
   for (int d = 0; d < fch; ++d) {
      dp_prv[d][false] = mul(pw10[sz - 1], d);
      ++cnt_prv[d];
   }
   dp_prv[fch][true] = mul(pw10[sz - 1], fch);

   for (int i = 1; i < sz; ++i) {
      int pw = pw10[sz - i - 1], cur_max = int(s[i] - '0'), prv_max = int(s[i - 1] - '0');

      for (int d = 0; d <= 9; ++d) {
         cnt_cur[d] = 0;
         for (bool last : {false, true}) {
            dp_cur[d][last] = 0;
         }
      }

      for (int d = 0; d <= 9; ++d) {
         for (int last_d = 0; last_d <= 9; ++last_d) {
            cnt_cur[d] = add(cnt_cur[d], cnt_prv[last_d]);
            dp_cur[d][false] = add(dp_cur[d][false], dp_prv[last_d][false]);
            if (d == last_d) continue;
            int factor = mul(cnt_prv[last_d], mul(pw, d));
            dp_cur[d][false] = add(dp_cur[d][false], factor);
         }
      }

      for (int d = 0; d < cur_max; ++d) {
         dp_cur[d][false] = add(dp_cur[d][false], dp_prv[prv_max][true]);
         cnt_cur[d] = add(cnt_cur[d], 1);

         if (d == prv_max) continue;
         int factor = mul(pw, d);
         dp_cur[d][false] = add(dp_cur[d][false], factor);
      }

      for (int d = 0; d <= 9; ++d)
         cnt_prv[d] = cnt_cur[d];

      dp_cur[cur_max][true] = add(dp_cur[cur_max][true], dp_prv[prv_max][true]);
      if (cur_max != prv_max) {
         int factor = mul(pw, cur_max);
         dp_cur[cur_max][true] = add(dp_cur[cur_max][true], factor);
      }
      for (int d = 0; d <= 9; ++d) {
         for (bool last : {false, true}) {
            dp_prv[d][last] = dp_cur[d][last];
         }
      }
   }
   int last = 0, not_last = 0;
   last = dp_prv[lch][true];

   for (int d = 0; d <= 9; ++d) {
      not_last = add(not_last, dp_prv[d][false]);
   }
   if (!take_last) {
      return not_last;
   }
   else return add(last, not_last);
}

signed main() {
   IOS; PREC;
   pw10.push_back(1);
   int tc, l, r;
   string L, R;
   cin >> tc;
   while (tc--) {
      cin >> l >> L >> r >> R;
      int upper = solve(R), lower = solve(L, false);
      cout << sub(upper, lower) << '\n';
   }

   return EXIT_SUCCESS;
}
