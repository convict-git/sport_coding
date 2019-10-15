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
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define x     first
#define y     second
using   ll  = long long;
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

const ll inf = (ll)1e18;
const int N = 17;
int n;
int a[N][N];
ll dp[1 << N];
ll wgt[1 << N];
vector <int> not_taken;
// dp[mask] := max wgt achieved if we have grouped 'mask' in optimal way
// new guess will be a whole new group (subset of not taken)
// wgt[mask] := weight of that mask according to the compatibility

void pre_proc() {
   //preprocessing in O(2^n * n^2) to get wgt of a group in O(1) time
   for (int mask = 0; mask < (1 << n); ++mask) {
      wgt[mask] = 0;
      for (int i = 0; i < n; ++i)
         for (int j = i + 1; j < n; ++j)
            if ((mask & (1 << i)) && (mask & (1 << j)))
               wgt[mask] += a[i][j];
   }
}

void solve_back_TLE() {
   // NOTE : TLE approac, in this we create dp from last calc (bottom up)
   // O(3^n * n) // THIS MAKES IT TLE (try to make it 3^n at max)
   // How is it 3^n * n ?   sum(nCk * 2^k * k) = n * 3^n
   dp[0] = 0;
   for (int mask = 1; mask < (1 << n); ++mask) { // O(3^n * n)
      dp[mask] = -inf;
      vector <int> taken;
      for (int i = 0; i < n; ++i)
         if (mask & (1 << i)) taken.push_back(i);

      int sz = (int)taken.size();
      for (int sb_mask = 0; sb_mask < (1 << sz); ++sb_mask) { // O(2^k * k)
         int real_mask = 0;
         for (int i = 0; i < sz; ++i) // O(k)
            if (sb_mask & (1 << i)) real_mask |= (1 << taken[i]);

         dp[mask] = max(dp[mask], dp[mask - real_mask] + wgt[real_mask]);
      }
   }
   cout << dp[(1 << n) - 1] << '\n';
}

void rec(int i, int new_group, int already) { // size of recursion tree O(2^k)
   if (i == (int)not_taken.size()) {
      // this is evaluated at the end of recursion tree (at leaves)
      // new_group is a subset of not_taken, whole = union(already, new_group)
      int whole = already | new_group;
      dp[whole] = max(dp[whole], dp[already] + wgt[new_group]);
      return;
   }
   rec(i + 1, new_group, already); // i not taken in new group
   rec(i + 1, new_group | (1 << not_taken[i]), already); //i taken in new group
}

void solve_fwd() {
   // NOTE:This approach is AC because it reduced the bottom up solution from
   //sum(nCk * 2^k * k) = 3^n * n to a topdown solution of sum(nCk * 2^k) = 3*n
   // Teaches us when to write a topdown and when to write a bottom up solution

   for (int i = 0; i < (1 << n); ++i) dp[i] = -inf;
   dp[0] = 0;

   // where k is size of mask, and
   // for each k you have only nCk masks
   // and for each such mask you go for 2^k recursion
   // now O(3^n) How ? sum(nCk * 2^k) = 3^n
   for (int mask = 0; mask < (1 << n); ++mask) { // O(3^n)
      not_taken.clear();
      for (int i = 0; i < n; ++i)
         if (!(mask & (1 << i))) not_taken.push_back(i);
      rec(0, 0, mask); // O(2^k)
   }
   cout << dp[(1 << n) - 1] << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n;
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         cin >> a[i][j];
   pre_proc();
   //solve_back_TLE(); // O(3^n * n) solution
   solve_fwd(); // O(3^n) solution
   return EXIT_SUCCESS;
}

