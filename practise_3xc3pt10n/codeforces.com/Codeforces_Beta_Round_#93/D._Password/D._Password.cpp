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

const int N = (int)2e6 + 10;
int pi[N];
int cnt[N];
string t;
int n;

void pref_func (string &s) {
   pi[0] = 0;
   int sz = (int)s.size();
   for (int i = 1; i < sz; ++i) {
      int len_j = pi[i-1]; // length of perfect prefix for i
      int j = len_j - 1; // index of end of perfect prefix for i
      while (len_j > 0 && s[j + 1] != s[i]) {
         len_j = pi[j];
         j = len_j - 1;
      }
      if (s[len_j] == s[i])
         ++len_j;
      pi[i] = len_j;
   }
}


void prefixCnt (string &s) {
   int N = (int)s.size();
   vector <int> cnt(N + 1);

   // pi : index -> length
   for (int i = 0; i < N; ++i) {
      cnt[pi[i]] += 1;
   }
   for (int i = N - 1; i >= 0; --i) {
      cnt[pi[i]] += cnt[i + 1];
   }
   for (int i = 1; i <= N; ++i) {
      cnt[i] += 1;
   }
}

void solve() {
   bool ok = false;
   pref_func(t);

   // Number of occurance of a prefix
   for (int i = 0; i < n; ++i)
      ++cnt[pi[i]];
   for (int i = n - 1; i >= 1; --i) {
      cnt[pi[i - 1]] += cnt[i]; // This doesn't make sense right?
   }
   for (int i = 0; i <= n; ++i)
   ++cnt[i];
   // prefixCnt(t);

   int len_j = pi[n - 1], j = len_j - 1;

   while (len_j > 0) {
      if (cnt[len_j] >= 3) {
         ok = true;
         break;
      }
      len_j = pi[j];
      j = len_j - 1;
   }

   if (!ok) {
      cout << "Just a legend\n";
   }
   else {
      for (int i = 0; i < len_j; ++i) cout << t[i];
      cout << '\n';
   }
}

signed main() {
   IOS; PREC;
   cin >> t;
   n = (int)t.size();
   solve();

   return EXIT_SUCCESS;
}
