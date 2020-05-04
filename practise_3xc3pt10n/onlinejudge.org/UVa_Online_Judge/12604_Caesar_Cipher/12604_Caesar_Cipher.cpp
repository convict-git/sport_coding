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

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt_rand(seed);

// seed_seq seq{
//    (uint64_t) chrono::duration_cast<chrono::nanoseconds>
//       (chrono::high_resolution_clock::now().time_since_epoch()).count(),
//       (uint64_t) __builtin_ia32_rdtsc(),
//       (uint64_t) (uintptr_t) make_unique<char>().get()
// };
// mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]

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

map <char, int> idx;

using Hash = pair <int, ull>;


struct polyhash {
   static const int Mod = (int)1e9 + 123;
   static vector <int> pow_int;
   static int p; // take p such that a[i] < p < Mod, gcd(p, Mod) = 1
   static int gen_base (const int l, const int r) {
      int base = uniform_int_distribution<int>(l + 1, r) (mt_rand);
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

   void encode(const string &st, int shift, int mx) {
      s.assign(sz, 0);
      for (int i = 0; i < sz; ++i) s[i] = ((idx[st[i]] - shift + mx) % mx) + 1;
      // for (int i = 0; i < sz; ++i) {cerr << "(" << s[i] << ", " << st[i] << ") ";} cerr << endl;
   }

   polyhash (const string &st, int shift, int mx) : sz((int)st.size())
   {
      encode(st, shift, mx);
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
const int N = 5e5 + 10;
string w, s, A;
int al, n, sz;

void solve() {
   // cerr << '\n';
   vector <int> freq(al, 0);
   polyhash word (w, 0, al);
   for (int shift = 0; shift < al; ++shift) {
      polyhash text_hash(s, shift, al);

      for (int i = 0; i + sz - 1 <= n - 1; ++i) {
         if (text_hash(i, sz, n) == word(0, sz, n)) {
            // cerr << "shift : " << shift << ' ' <<  " i: " << i << " word "  << w << ' ' << " sub : " << s.substr(i, sz) << endl;
            ++freq[shift];
         }
      }
   }

   vector <int> ans;
   for (int shift = 0; shift < al; ++shift) {
      if (freq[shift] == 1) ans.push_back(shift);
      if (freq[shift] >= 2) freq[shift] = 0;
   }

   if ((int)ans.size() == 0) {
      cout << "no solution\n";
   }
   else if ((int)ans.size() == 1) {
      cout << "unique: " << ans.back() << '\n';
   }
   else {
      cout << "ambiguous: ";
      for (int i = 0; i < (int)ans.size(); ++i) {
         cout << ans[i] << " \n"[i == (int)ans.size() - 1];
      }
   }
}

void read() {
   cin >> A >> w >> s;
   idx.clear();
   al = (int)A.size(), n = (int)s.size();
   sz = (int)w.size();

   for (int i = 0; i < al; ++i) {
      idx[A[i]] = i;
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read(), solve();
   }

   return EXIT_SUCCESS;
}
