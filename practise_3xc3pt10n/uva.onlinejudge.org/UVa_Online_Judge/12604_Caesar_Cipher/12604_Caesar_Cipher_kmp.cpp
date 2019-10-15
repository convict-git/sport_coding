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
const int N = 5e5 + 10;
string w, s, A;
int al, text_sz, word_sz;

void solve() {
   vector <int> freq(al, 0);
   vector <int> pi(text_sz + word_sz + 1, 0);
   string kmp = w + '#' + s;
   for (int shift = 0; shift < al; ++shift) {
      pi[0] = 0;

      for (int i = 1; i < text_sz + word_sz + 1; ++i) {
         if (i == word_sz) {
            pi[i] = 0;
            continue;
         }
         int j_len = pi[i - 1];
         int j = j_len - 1;

         if (i <= word_sz) {
            while (j_len > 0 && idx[kmp[j + 1]] != idx[kmp[i]]) {
               j_len = pi[j];
               j = j_len - 1;
            }
            if (idx[kmp[j + 1]] == idx[kmp[i]])
               ++j_len;

            pi[i] = j_len;
         }
         else {
            while (j_len > 0 && (shift + idx[kmp[j + 1]]) % al != idx[kmp[i]]) {
               j_len = pi[j];
               j = j_len - 1;
            }
            if ((shift + idx[kmp[j + 1]]) % al == idx[kmp[i]])
               ++j_len;

            pi[i] = j_len;
         }
      }
      for (int i = word_sz + 1; i < text_sz + word_sz + 1; ++i)
         if (pi[i] == word_sz) ++freq[shift];
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
   al = (int)A.size(), text_sz = (int)s.size();
   word_sz = (int)w.size();

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
