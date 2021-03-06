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

const int N = 101;
int Ar[N][N];
int n, q;

void print0() {
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
         cout << Ar[i][j] << " \n"[j == n - 1];
      }
   }
}

void print1() {
   for (int j = 0; j < n; ++j) {
      for (int i = n - 1; i >= 0; --i) {
         cout << Ar[i][j] << " \n"[i == 0];
      }
   }
}

void print2() {
   for (int i = n - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
         cout << Ar[i][j] << " \n"[j == 0];
      }
   }
}

void print3() {
   for (int j = n - 1; j >= 0; --j) {
      for (int i = 0; i < n; ++i) {
         cout << Ar[i][j] << " \n"[i == n - 1];
      }
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      int state = 0;
      cin >> n >> q;
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            cin >> Ar[i][j];
      string s; int cnt;
      while (q--) {
         cin >> s >> cnt;
         cnt %= 4;
         if (s == "L") {
            state = (state - cnt + 4) % 4;
         }
         else state = (state + cnt) % 4;
      }
      if (state == 0) print0();
      else if (state == 1) print1();
      else if (state == 2) print2();
      else if (state == 3) print3();
   }

   return EXIT_SUCCESS;
}
