#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
// #pragma GCC   optimize ("Ofast")
// #pragma GCC   optimize ("unroll-loops")
// #pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//
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

// auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
// mt19937 rng(seed); //uniform_int_distribution<T> (l, h)(rng); //[low, high]

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

#include <bits/stdc++.h>
using namespace std;
// #WARNING "for n=5e6 this can timeout so just go for single hashing then"
// #WARNING "Optimization flags kill polyhash, use it wisely!"
using ull = unsigned long long;
using Hash = pair <int, ull>;
seed_seq seq{
   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
      (uint64_t) __builtin_ia32_rdtsc(),
      (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]

class polyhash {
   public:
      static const int Mod = (int)1e9 + 123;
      static vector <int> pow_int;
      static vector <ull> pow_ull;
      static int p; // take p such that a[i] < p < Mod, gcd(p, Mod) = 1

      static int gen_base (const int l, const int r) {
         int base = uniform_int_distribution<int>(l + 1, r - 1) (rng);
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

      inline Hash operator()
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

      bool compare (int i, int len1, int j, int len2, int mx_len) // hash of whole string
      {
         assert(i + len1 <= sz && j + len2 <= sz);
         int len = min(len1, len2);
         int l = 1, h = len;
         while (l <= h) {
            int glen = (l + h)/2;
            if ((*this)(i, glen, mx_len) == (*this)(j, glen, mx_len))
               l = glen + 1;
            else h = glen - 1;
         }
         if (l > len) {//l is length of first point of difference
            return len1 < len2;
         }
         return s[i + l - 1] < s[j + l - 1];
      }

      Hash inf_ext(int i, int len, int o_len, int mx_len) {
         function <ull(ull, int)> gp_ull = [&](ull a, int k) -> ull {
            ull a_sq = a * a;
            if (k == 1) return 1;
            else if (k & 1) return 1 + a * gp_ull(a, k - 1);
            else return (1 + a) * gp_ull (a_sq, k/2);
         };
         function <int(int, int)> gp_int = [&] (int a, int k)->int {
            int a_sq = int(1ll * a * a % Mod);
            if (k == 1) return 1;
            else if (k & 1) return int((1 + (1ll * a * gp_int(a, k - 1) % Mod)));
            else return int(1ll * (1 + a) * gp_int (a_sq, k/2) % Mod);
         };

         Hash h = (*this)(i, len, mx_len);
         int hx = int(1ll * h.first * pow_int[len] % Mod);
         ull hy = h.second * pow_ull[len] * gp_ull(p, o_len);
         hx = int(1ll * hx * gp_int(p, o_len) % Mod);
         return make_pair(hx, hy);
      }
};

int polyhash::p = polyhash::gen_base(256, polyhash::Mod);
vector <int> polyhash::pow_int{1};
vector <ull> polyhash::pow_ull{1};
// int polyhash::p = 31; // 31 for [a ... z], 53 for [a..z, A..Z]

string s;
void solve() {
   int len = (int)s.size();
   polyhash hash(s);

   int cnt = 0;
   for (int l = 1; l <= len; ++l) {
      if (hash.inf_ext(0, l, len, len) == hash.inf_ext(0, len, l, len))
         ++cnt;
   }
   cout << cnt << '\n';
}

signed main() {
   IOS; PREC;
   cin >> s;
   reverse(s.begin(), s.end());
   solve();

   return EXIT_SUCCESS;
}
