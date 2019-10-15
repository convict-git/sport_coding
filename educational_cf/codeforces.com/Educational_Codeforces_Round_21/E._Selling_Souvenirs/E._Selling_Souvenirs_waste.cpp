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

#if __cplusplus > 201103L
seed_seq seq{
   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
      (uint64_t) __builtin_ia32_rdtsc(),
      (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]
#else
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed);
#endif

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

signed main() {
   IOS; PREC;

   int n, m;
   cin >> n >> m;
   priority_queue <int> one, two, three;
   for (int i = 0; i < n; ++i) {
      int wi, ci;
      cin >> wi >> ci;
      if (wi == 1)one.push(ci);
      else if (wi == 2) two.push(ci);
      else three.push(ci);
   }

   auto get_one = [&] (void) -> int {
      if (one.empty()) return 0;
      int cost = one.top();
      one.pop();
      return cost;
   };

   auto get_two = [&] (void) -> int {
      // (1, 1) or (2)
      if (two.empty() && one.size() < 2) return 0;

      int c1_x = 0, c1_y = 0, c1 = 0;
      if (one.size() >= 2) {
         c1_x = one.top();
         one.pop();
         c1_y = one.top();
         one.pop();
         c1 = c1_x + c1_y;
      }
      int c2 = 0;
      if (!two.empty()) {
         c2 = two.top();
         two.pop();
      }
      if (c1 > c2) {
         if (c2) two.push(c2);
         return c1;
      }
      else {
         if (c1_x) one.push(c1_x);
         if (c1_y) one.push(c1_y);
         return c2;
      }
   };

   auto get_three = [&] (void) -> int {
      // (1, 1, 1), (1, 2), (3)
      if (three.empty() && one.size() < 3 && (one.empty() && two.empty()))
         return 0;
      int c1_x = 0, c1_y = 0, c1_z = 0, c1 = 0;
      if (one.size() >= 3) {
         c1_x = one.top(), one.pop();
         c1_y = one.top(), one.pop();
         c1_z = one.top(), one.pop();
         c1 = c1_x + c1_y + c1_z;
      }
      int c2_x = 0, c12 = 0;
      if (!two.empty() && !one.empty()) {
         c2_x = two.top(), one.pop();
         c12 = c1_x + c2_x;
      }

      int c3 = 0;
      if (!three.empty()) {
         c3 = three.top();
         three.pop();
      }
      int mx = max({c1, c12, c3});
      if (mx == c3) {
         if (c1_x) one.push(c1_x);
         if (c1_x) one.push(c1_y);
         if (c1_z) one.push(c1_z);
         if (c2_x) two.push(c2_x);
         return c3;
      }
      else if (mx == c12) {
         if (c3)three.push(c3);
         if (c1_y) one.push(c1_y);
         if (c1_z) one.push(c1_z);
         return c12;
      }
      else {
         if (c3) three.push(c3);
         if (c2_x) two.push(c2_x);
         return c1;
      }
   };

   ll total_cost = 0;
   while (m) {
      bool ok = false;
      if (m >= 3) {
         int cost = get_three();
         if (cost) {
            total_cost += cost;
            ok = true;
            m -= 3;
         }
      }
      if (m >= 2 && !ok) {
         int cost = get_two();
         if (cost) {
            total_cost += cost;
            ok = true;
            m -= 2;
         }
      }
      if (m >= 1 && !ok) {
         int cost = get_one();
         if (cost) {
            total_cost += cost;
            ok = true;
            m -= 1;
         }
      }
      if (!ok) break;
   }
   cout << total_cost << '\n';
   return EXIT_SUCCESS;
}
