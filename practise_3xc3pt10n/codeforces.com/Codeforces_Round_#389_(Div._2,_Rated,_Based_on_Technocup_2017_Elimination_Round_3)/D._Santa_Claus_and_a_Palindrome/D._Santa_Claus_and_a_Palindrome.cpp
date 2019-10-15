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
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update >
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

using Hash = pair <int, ull>;
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

int b = (int)1e9 + 7;
int polyhash::p = polyhash::gen_base(b, polyhash::Mod - 1);
vector <int> polyhash::pow_int{1};
vector <ull> polyhash::pow_ull{1};


const int N = (int)1e6 + 10;
vector <pair <pii, bool>> hashes;
vector <pair <Hash, pii>> for_hash, rev_hash;
int n, k;
bool used[N];
int match_val[N];
const int infi = (int)1e9;

void solve() {
   stable_sort(for_hash.begin(), for_hash.end());
   stable_sort(rev_hash.begin(), rev_hash.end());
   fill (used, used + k, false);
   fill (match_val, match_val + k, 0);
   vector <pii> idx_lost(k, pii(-1,-1));

   for (int i = 0; i < k; ++i) {
      idx_lost[for_hash[i].y.y].x = i;
      idx_lost[rev_hash[i].y.y].y = i;
   }

   // for (int i = 0; i < k; ++i) { debug(for_hash[i].x.x, for_hash[i].x.y, -1*for_hash[i].y.x, for_hash[i].y.y); }
   // cerr << '\n'; for (int i = 0; i < k; ++i) { debug(rev_hash[i].x.x, rev_hash[i].x.y, -1*rev_hash[i].y.x, rev_hash[i].y.y); }

   ll ans = 0;

   for (int i = 0; i < k; ++i) {
      int cur_idx = for_hash[i].y.y;
      // debug(cur_idx, idx_lost[cur_idx].y);
      if (used[cur_idx]) continue;
      Hash cur_hash = for_hash[i].x;
      int cur_val = -1*for_hash[i].y.x;

      pii ans_l = pii(-infi, -1), ans_r = pii(-infi, -1);

      //search in first half
      //first half h = idx_lost[cur_idx].y - 1
      //second half l = idx_lost[cur_idx].y + 1

      int l = 0, h = idx_lost[cur_idx].y - 1;
      // debug(h);
      while (l <= h) { // find the second half of the palindrome
         int g = (l + h)/2;
         Hash g_hash = rev_hash[g].x;
         int g_idx = rev_hash[g].y.y;

         if (g_hash == cur_hash) {
            if (used[g_idx]) l = g + 1;
            else h = g - 1;
         }
         else if (g_hash < cur_hash) l = g + 1;
         else h = g - 1;
      }
      if (l >= 0 && l < idx_lost[cur_idx].y && (cur_hash == rev_hash[l].x)) {
         ans_l = make_pair(-1*rev_hash[l].y.x, rev_hash[l].y.y);
      }

      l = idx_lost[cur_idx].y + 1, h = k - 1;
      // debug(l);
      while (l <= h) {
         int g = (l + h)/2;
         Hash g_hash = rev_hash[g].x;
         int g_idx = rev_hash[g].y.y;

         if (g_hash == cur_hash) {
            if (used[g_idx]) l = g + 1;
            else h = g - 1;
         }
         else if (g_hash < cur_hash) l = g + 1;
         else h = g - 1;
      }

      if (l >= idx_lost[cur_idx].y + 1 && l < k && (cur_hash == rev_hash[l].x)) {
         ans_r = make_pair(-1*rev_hash[l].y.x, rev_hash[l].y.y);
      }

      if (ans_l.x == -infi && ans_r.x == -infi) {
         //nothing matches
      }
      else {
         if (ans_l.x > ans_r.x && cur_val + ans_l.x > 0) {
             // debug(cur_val, ans_l.x);
            ans += 1ll*(cur_val + ans_l.x);
            used[cur_idx] = used[ans_l.y] = true;
            match_val[cur_idx] = ans_l.x;
         }
         else if (ans_r.x >= ans_l.x && cur_val + ans_r.x > 0) {
            // debug(cur_val, ans_r.x);
            ans += 1ll*(cur_val + ans_r.x);
            used[cur_idx] = used[ans_r.y] = true;
            match_val[cur_idx] = ans_r.x;
         }
         // else assert(false);
      }
   }

   sort(hashes.begin(), hashes.end());
   int z = 0;
   for (int i = 0; i < k; ++i) {
      int idx = hashes[i].x.y;
      int val = -1*hashes[i].x.x;
      bool is_pal = hashes[i].y;
      if (is_pal && val > 0){
         if (used[idx] && match_val[idx] < 0) {
            z = max(z, -1*match_val[idx]);
         }
         else if (!used[idx]) {
            z = max(z, val);
         }
      }
   }
   cout << ans + z << '\n';
}

void read() {
   cin >> k >> n;
   for (int i = 0; i < k; ++i) {
      string foo;
      int a_val;
      cin >> foo >> a_val;
      polyhash hash_f(foo);
      reverse(foo.begin(), foo.end());
      polyhash hash_b(foo);

      bool is_pal = (hash_f(0, n, n) == hash_b(0, n, n));
      hashes.emplace_back(make_pair(-1*a_val, i), is_pal);
      for_hash.emplace_back(hash_f(0, n, n), make_pair(-1*a_val, i));
      rev_hash.emplace_back(hash_b(0, n, n), make_pair(-1*a_val, i));
   }
}

signed main() {
   IOS; PREC;
   read(), solve();

   return EXIT_SUCCESS;
}
