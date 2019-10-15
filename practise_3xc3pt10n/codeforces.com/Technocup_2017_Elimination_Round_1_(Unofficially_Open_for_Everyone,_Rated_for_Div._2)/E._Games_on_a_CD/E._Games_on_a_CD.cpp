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
      while ((int)pow_int.size() <= mx_len) { // calc powers
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
   //string a; polyhash hash_a(a); if (hash_a(i, len, sz) == hash_b(j, len, sz))
   //indexing from 0, len >= 1
};

int polyhash::p = polyhash::gen_base((int)1e6 + 10, polyhash::Mod);
vector <int> polyhash::pow_int{1};
vector <ull> polyhash::pow_ull{1};
// int polyhash::p = 31; // 31 for [a ... z], 53 for [a..z, A..Z]

const int N = (int)2e6 + 10;
string t;
int n, k, q;
vector <pair <pair <int, ull>, int>> hashes;
bool found[N];
int ans[N];
int mxpw;

void solve() {
   bool ok = true;
   polyhash hash(t);
   sort(hashes.begin(), hashes.end());
   fill(found, found + k, false);
   int f_cnt = 0;

   for (int i = 0; i < k; ++i) {
      pair <int, ull> cur_hash = hash(i, k, mxpw);
      int l = 0, h = (int)hashes.size() - 1;
      while (l <= h) {
         int g = (l + h)/2;
         if (hashes[g].x == cur_hash) {
            found[i] = true;
            ++f_cnt;
            break;
         }
         else if (hashes[g].x < cur_hash) {
            l = g + 1;
         }
         else h = g - 1;
      }
   }

   if (f_cnt == 0) {
      ok = false;
   }
   else {
      assert (1ll * f_cnt * n <= (ll)1e6);

      vector <bool> used(q, false);
      for (int i = 0; i < k; ++i) {
         if (found[i]) {
            ok = true;
            used.assign(q, false); // it can not be reused again
            for (int j = 0; j < n; ++j) {
               bool well = false;
               pair <int, ull> cur_hash = hash(i + k*j, k, mxpw);
               int l = 0, h = (int)hashes.size() - 1;
               while (l <= h) {
                  int g = (l + h)/2;
                  if (hashes[g].x == cur_hash) {
                     if (used[g]) {
                        well = false;
                        break;
                     }
                     used[g] = true;
                     ans[j] = hashes[g].y;
                     well = true;
                     break;
                  }
                  else if (hashes[g].x < cur_hash) {
                     l = g + 1;
                  }
                  else h = g - 1;
               }
               if (!well) {
                  ok = false;
                  break;
               }
            }
            if (ok) break;
         }
      }
   }
   if (ok) {
      cout << "YES\n";
      for (int i = 0; i < n; ++i) {
         cout << ans[i] + 1 << " \n"[i == n - 1];
      }
   }
   else {
      cout << "NO\n";
   }
}

void read() {
   cin >> n >> k >> t;
   t += t;
   mxpw = (int)t.size();
   polyhash::calc_pow(mxpw);
   cin >> q;
   hashes.clear();
   for (int i = 0; i < q; ++i) {
      string foo;
      cin >> foo;
      polyhash hash_tmp(foo);
      hashes.emplace_back(hash_tmp(0, k, mxpw), i);
   }
}

signed main() {
   IOS; PREC;
   read(), solve();

   return EXIT_SUCCESS;
}
