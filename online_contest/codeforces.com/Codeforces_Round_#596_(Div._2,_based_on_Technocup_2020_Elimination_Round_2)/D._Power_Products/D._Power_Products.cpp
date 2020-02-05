#include      <bits/stdc++.h> /*{{{*/
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifndef CONVICTION
#pragma GCC       optimize ("Ofast")
#pragma GCC       optimize ("unroll-loops")
#pragma GCC       target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define x         first
#define y         second
#define fr(i,x,y) for (int i = x; i <= y; ++i)
#define fR(i,x,y) for (int i = x; i >= y; --i)
#define cnt(x)    __builtin_popcount(x)
#define cntll(x)  __builtin_popcountll(x)
#define bg(x)     " [ " << #x << " : " << (x) << " ] "
#define un(x)     sort(x.begin(), x.end()), \
                  x.erase(unique(x.begin(), x.end()), x.end())
using   ll  =     long long;
using   ull =     unsigned long long;
using   ff  =     long double;
using   pii =     pair<int,int>;
using   pil =     pair<int,ll>;
using   vi  =     vector <int>;
using   vvi =     vector <vi>;
using   vp  =     vector <pii>;
using   vl  =     vector<ll>;
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
/*}}}*/
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong

signed main() {
   IOS; PREC;

   int n, k;
   cin >> n >> k;
   vector <ff> a(n);

   ff mx = 0;
   fr(i, 0, n-1) cin >> a[i], a[i] = log2(a[i]), mx = max(mx, a[i]);

   ff lk = log2(k);
   ff limit = 2 * mx;
   vector <pair <ff, int>> A(n);
   fr(i, 0, n-1) A[i] = make_pair(a[i], i);
   sort (A.begin(), A.end());

   fr(i, 0, n-1) a[i] = A[i].x;

   int final_ans = 0;

   ff eps = 1e-9;
   fr (i, 0, n-1) {
      cerr << "searching for a[i] " << pow(2, a[i]) << endl;
      int cnt = 0;
      for (int x = 1; x <= limit + 1; ++x) {

         ff find = x * lk - a[i];

         int l = 0, h = n-1;
         while (l <= h) {
            int g = (l+h)/2;
            if (fabs(a[g] - find) <= eps || a[g] >= find) // check equality
               h = g - 1;
            else l = g + 1;
         }
         int left = l;

         l = 0, h = n-1;
         while (l <= h){
            int g = (l+h)/2;
            if (abs(a[g] - find) <= eps || a[g] <= find) // check equality
               l = g + 1;
            else h = g - 1;
         }
         int right = h;

         if (left <= right) {
            cerr << "is number : " << x << endl;
            // cerr << "got it : " << A[i].y << ' ' << pow(2, a[i]) << ' ' << pow(2, find) << ' ' << pow(x, k) << endl;
            cnt += (right - left  + 1);
            if (fabs(2 * a[i] - x * lk) <= eps) --cnt;
         }
      }
      final_ans += cnt;
   }
   cout << final_ans/2 << '\n';
   return EXIT_SUCCESS;
}
