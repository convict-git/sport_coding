#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
// #pragma GCC   optimize ("Ofast")
// #pragma GCC   optimize ("unroll-loops")
// #pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

struct polyhash {
   using ull = unsigned long long;
   static const int Mod = (int)1e9 + 123;
   static vector <int> pow_int;
   static vector <ull> pow_ull;
   static int p; // take p such that a[i] < p < Mod, gcd(p, Mod) = 1
   static int gen_base (const int l, const int r) {
      int base = uniform_int_distribution<int>(l + 1, r) (rng);
      return base % 2 == 0 ? base - 1 : base;
   }
   static void calc_pow(int mx_len) {
      while ((int)pow_int.size() <= mx_len + 1) { // calc powers
         pow_int.push_back(int(1ll * pow_int.back() * p % Mod));
         pow_ull.push_back(pow_ull.back() * p);
      }
   }
   const int sz;

   vector <int> s;
   vector <int> pref_int;
   vector <ull> pref_ull;

   void encode(const string &st) {
      s.assign(sz, 0);
      for (int i = 0; i < sz; ++i) s[i] = st[i];
   }

   polyhash (const string &st) : sz((int)st.size())
   {
      encode(st);
      pref_int.assign(sz + 1u, 0);
      pref_ull.assign(sz + 1u, 0);
      assert(p < Mod);

      calc_pow(sz + 1);

      for (int i = 0; i < sz; ++i) {
         assert(p > s[i]);
         pref_int[i] = int(1ll*s[i]*pow_int[i] % Mod);
         pref_int[i] = (pref_int[i] + (i > 0 ? pref_int[i - 1] : 0)) % Mod;
         pref_ull[i] = s[i]*pow_ull[i] + (i > 0 ? pref_ull[i - 1] : 0);
      }
   }

   inline pair <int, ull> operator()
      (const int pos, const int len, const int mx_len = -1) const
      {
         assert(pos + len <= sz);
         int hash_int = pref_int[pos + len - 1];
         ull hash_ull = pref_ull[pos + len - 1];
         if (pos != 0) {
            hash_int = (hash_int - pref_int[pos - 1] + Mod) % Mod;
            hash_ull = hash_ull - pref_ull[pos - 1];
         }
         if (mx_len != -1) { // for direct comparison between prefixes
            //else multiply with opposite powers
            assert (mx_len < (int)pow_int.size());
            hash_int = int(1ll*hash_int*pow_int[mx_len - (pos+len-1)] % Mod);
            hash_ull *= pow_ull[mx_len - (pos+len-1)];
         }
         return make_pair(hash_int, hash_ull);
      }
   //indexing from 0, len >= 1
};

int polyhash::p = polyhash::gen_base((int)256, polyhash::Mod);
vector <int> polyhash::pow_int{1};
vector <ull> polyhash::pow_ull{1};
// int polyhash::p = 31; // 31 for [a ... z], 53 for [a..z, A..Z]

const int N = 5005;
int n;
string s;
int dp[N][N];

bool k_pal (int i, int j, int k, polyhash& for_h, polyhash& rev_h) {
   bool ok = false;
   int len = j - i + 1;
   if (j < i) return false;
   if (k <= dp[i][j]) ok = true;
   else if (k == 1) {
      ok = (for_h(i, len, n) == rev_h(n - (i + len - 1) - 1, len, n));
   }
   else {
      int j_l, i_r;
      int new_len = (len)/2;
      j_l = i + new_len - 1;
      i_r = j - new_len + 1;
      if (for_h(i, new_len, n) == for_h(i_r, new_len, n)) {
         bool lf = k_pal(i, j_l, k - 1, for_h, rev_h);
         // bool rt = k_pal(i_r, j, k - 1, for_h, rev_h);
         ok = lf;
      }
      else ok = false;
   }
   if (ok) {
      dp[i][j] = max(dp[i][j], k);
   }
   return ok;
}

void solve() {
   n = (int)s.size();
   polyhash for_hash(s);
   reverse(s.begin(), s.end());
   polyhash rev_hash(s);
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         dp[i][j] = 0;

   vector <int> kval(n, 0);
   for (int len = n; len >= 1; --len) {
      for (int i = 0; i + len - 1 <=  n - 1; ++i) {
         int j = i + len - 1;
         for (int k = 1; k <= int(floor(sqrt(n))) + 1; ++k) {
            if (for_hash(i, len, n) == rev_hash(n - (i + len - 1) - 1, len, n)) {
               if (dp[i][j] >= k)
                  ++kval[k - 1];
               else
                  kval[k - 1] += k_pal(i, j, k, for_hash, rev_hash);
            }
         }
      }
   }
   for (int i = 0; i < n; ++i) {
      cout << kval[i] << " \n"[i == n - 1];
   }
}

signed main() {
   IOS; PREC;
   cin >> s;
   solve();

   return EXIT_SUCCESS;
}
