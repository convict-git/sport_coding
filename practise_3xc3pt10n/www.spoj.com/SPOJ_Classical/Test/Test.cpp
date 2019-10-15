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

struct polyhash {
   static const int Mod = (int)1e9 + 123;
   static vector <int> pow_int;
   static int p; // take p such that a[i] < p < Mod, gcd(p, Mod) = 1
   static int gen_base (const int l, const int r) {
      int base = uniform_int_distribution<int>(l + 1, r) (rng);
      return base % 2 == 0 ? base - 1 : base;
   }
   static void calc_pow(int mx_len) {
      while ((int)pow_int.size() <= mx_len + 1) { // calc powers
         pow_int.push_back(int(1ll * pow_int.back() * p % Mod));
      }
   }
   const int sz;

   vector <int> s;
   vector <int> pref_int;

   void encode(const string &st) {
      s.assign(sz, 0);
      for (int i = 0; i < sz; ++i) s[i] = st[i];
   }

   polyhash (const string &st) : sz((int)st.size())
   {
      encode(st);
      pref_int.assign(sz + 1u, 0);
      assert(p < Mod);

      calc_pow(sz + 1);

      for (int i = 0; i < sz; ++i) {
         assert(p > s[i]);
         pref_int[i] = int(1ll*s[i]*pow_int[i] % Mod);
         pref_int[i] = (pref_int[i] + (i > 0 ? pref_int[i - 1] : 0)) % Mod;
      }
   }

   inline int operator()
      (const int pos, const int len, const int mx_len = -1) const
      {
         assert(pos + len <= sz);
         int hash_int = pref_int[pos + len - 1];
         if (pos != 0) {
            hash_int = (hash_int - pref_int[pos - 1] + Mod) % Mod;
         }
         if (mx_len != -1) { // for direct comparison between prefixes
            //else multiply with opposite powers
            assert (mx_len < (int)pow_int.size());
            hash_int = int(1ll*hash_int*pow_int[mx_len - (pos+len-1)] % Mod);
         }
         return hash_int;
      }
   //indexing from 0, len >= 1
};

int polyhash::p = polyhash::gen_base((int)256, polyhash::Mod);
vector <int> polyhash::pow_int{1};
// int polyhash::p = 31; // 31 for [a ... z], 53 for [a..z, A..Z]

vector <string> s;
pair <string, string> get_best(string &big, string &small) {
   int n = (int)big.size(), m = (int)small.size();
   polyhash hash_big(big), hash_small(small);

   //smaller contained inside
   for (int i = 0; i  + m - 1 <= n - 1; ++i) {
      if (hash_big(i, m, n) == hash_small(0, m, n)) {
         return make_pair(big, big);
      }
   }

   int mx_len1 = 0, mx_len2 = 0;
   for (int i = 0; i < m; ++i) {
      //smaller shares its suffix with biggers prefix
      int len1 =  m - i;
      if (hash_big(0, len1, n) == hash_small(i, len1, n))
         mx_len1 = max(mx_len1, len1);

      //smaller shares its prefix with biggers suffix
      int len2 = i + 1;
      if (hash_big(n - len2, len2, n) == hash_small(0, len2, n))
         mx_len2 = max(mx_len2, len2);
   }

   if (mx_len1 == 0 && mx_len2 == 0) {
      return make_pair(big + small, small + big);
   }
   else {
      if (mx_len1 > mx_len2) {
         big = small.substr(0, m - mx_len1) + big;
      }
      else {
         big = big + small.substr(mx_len2, m - mx_len2);
      }
      return make_pair(big, big);
   }
}

void solve() {
   int ans = (int)(s[0].size() + s[1].size() + s[2].size());
   vector <int> idx = {0, 1, 2};
   do{
      pair <string, string> best, ans1, ans2;
      string big, small;
      if (s[idx[0]].size() > s[idx[1]].size()) big = s[idx[0]], small = s[idx[1]];
      else big = s[idx[1]], small = s[idx[0]];
      best = get_best(big, small);

      if (best.x.size() > s[idx[2]].size()) big = best.x, small = s[idx[2]];
      else big = s[idx[2]], small = best.x;
      ans1 = get_best(big, small);

      if (best.y.size() > s[idx[2]].size()) big = best.y, small = s[idx[2]];
      else big = s[idx[2]], small = best.y;
      ans2 = get_best(big, small);


      int local_ans = min({ans1.x.size(), ans1.y.size(), ans2.x.size(), ans2.y.size()});
      ans = min(ans, local_ans);
   } while (next_permutation(idx.begin(), idx.end()));

   cout << ans << '\n';
}

signed main() {
   IOS; PREC;
   s.resize(3);
   while (cin >> s[0] >> s[1] >> s[2]) {
      solve();
   }

   return EXIT_SUCCESS;
}
