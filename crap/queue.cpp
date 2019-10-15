#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifndef CONVICTION
#pragma GCC   optimize ("Ofast")
#pragma GCC   optimize ("unroll-loops")
#pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

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
   int operator () (pii x) const { return x.x*31 + x.y; }
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
//Don’t practice until you get it right. Practice until you can’t get it wrong

signed main() {
   IOS; PREC;

   int n;
   cin >> n;
   vector <int> A(n);
   for (int i = 0; i < n; ++i) {
      cin >> A[i];
   }

   queue <int> Q;
   vector <int> cost(n, 0);

   //cerr << "InQueue : " ;
   vector <int> cnt(n, 0);
   for (int i = 0; i < n; ++i) {
      if (i == 0 && i + 1 <= n - 1 && A[i] <= A[i + 1]) {
         cost[i] = 100;
         Q.push(i);
         ++cnt[i];
         //cerr << A[i] << ' ';
      }
      else if (i == n - 1 && i - 1 >= 0 && A[i] <= A[i - 1]) {
         cost[i] = 100;
         Q.push(i);
         ++cnt[i];
         //cerr << A[i] << ' ';
      }
      else if (i + 1 <= n - 1 && i - 1 >= 0 && A[i] <= A[i + 1] && A[i] <= A[i - 1]) {
         cost[i] = 100;
         Q.push(i);
         ++cnt[i];
         //cerr << A[i] << ' ';
      }
   }
   //cerr << '\n';
   while (!Q.empty()) {
      for (int i = 0; i < n; ++i) {
         cerr << cnt[i] << " \n" [i == n - 1];
      }
      cerr << endl;
      int u = Q.front();
      Q.pop();
      //cerr << "Popped Out : " << A[u] << '\n';
      if (u + 1 <= n - 1 && A[u] <= A[u + 1]) {
         cost[u + 1] = max(cost[u + 1], cost[u] + 100);
         Q.push(u + 1);
         ++cnt[u + 1];
         //cerr << "right : " << cost[u + 1] << ' ';
      }
      if (u - 1 >= 0 && A[u] <= A[u - 1]) {
         cost[u - 1] = max(cost[u - 1], cost[u] + 100);
         Q.push(u - 1);
         ++cnt[u - 1];
         //cerr << "left : " << cost[u - 1] << ' ';
      }
      //cerr << '\n';
   }

   for (int i = 0; i < n; ++i) {
      cout << A[i] << " \n" [i == n - 1];
   }
   for (int i = 0; i < n; ++i) {
      cout << cost[i] << " \n" [i == n - 1];
   }

   return EXIT_SUCCESS;
}

