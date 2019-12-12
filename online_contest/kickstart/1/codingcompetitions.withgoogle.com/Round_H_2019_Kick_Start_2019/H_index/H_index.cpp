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
#define fr(i,x,y) for (int i = (int)x; i <= (int)y; ++i)
#define rv(i,x,y) for (int i = (int)x; i >= (int)y; --i)
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
using   vl  =     vector<ll>;
using   vvi =     vector <vi>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
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
//         __                                           __
//        (**)                                         (**)
//        IIII                                         IIII
//        ####                                         ####
//        HHHH     Madness comes, and madness goes     HHHH
//        HHHH    An insane place, with insane moves   HHHH
//        ####   Battles without, for battles within   ####
//     ___IIII___        Where evil lives,          ___IIII___
//  .-`_._"**"_._`-.      and evil rules         .-`_._"**"_._`-.
// |/``  .`\/`.  ``\|    Breaking them up,      |/``  .`\/`.  ``\|
// `     }    {     '  just breaking them in    `     }    {     '
//       ) () (  Quickest way out, quickest way wins  ) () (
//       ( :: )      Never disclose, never betray     ( :: )
//       | :: |   Cease to speak or cease to breath   | :: |
//       | )( |        And when you kill a man,       | )( |
//       | || |          you're a murderer            | || |
//       | || |             Kill many                 | || |
//       | || |        and you're a conqueror         | || |
//       | || |        Kill them all ... Ooh..        | || |
//       | || |           Oh you're a God!            | || |
//       ( () )                       -Megadeth       ( () )
//        \  /                                         \  /
//         \/                                           \/
/*}}}*/
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong

#include <bits/stdc++.h>
using namespace std;

class seg_sum { /*{{{*/
   // Recurisve Segment Tree with lazy propogation for sum library
   // This library is created by Priyanshu Shrivastav (mr.convict)
   // https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/segment_tree_sum.cpp
   public:
      using ll = long long;
      seg_sum (int n, int Ar[] = nullptr) {
         sz = n;
         if (Ar == nullptr)
            memset(ar, 0, sizeof(ar));
         else for (int i = 0; i < sz; ar[i] = Ar[i], ++i);
         create(0, n - 1, 0);
      }
      seg_sum(int n, vector <int> Ar) {
         sz = n;
         assert((int)Ar.size() == n);
         for (int i = 0; i < sz; ar[i] = Ar[i], ++i);
         create(0, n - 1, 0);
      }

      static const int MXN = (int)2e5 + 10;
      int sz;
      int ar[MXN];
      ll seg[4 * MXN], lz[4 * MXN];

      void create (int l, int r, int x) {
         lz[x] = 0;
         if (l == r)
         {
            seg[x] = ar[l];
            return;
         }
         int mid = (l + r)/2;
         create(l, mid, x + x + 1);
         create(mid + 1, r, x + x + 2);
         seg[x] = seg[x + x + 1] + seg[x + x + 2];
      }

      void lz_upd(int l, int r, int x) {
         if (lz[x] != 0) {
            seg[x] += 1ll * (r - l + 1) * lz[x];
            if (l != r)
            {
               lz[x + x + 1] += lz[x];
               lz[x + x + 2] += lz[x];
            }
            lz[x] = 0;
            return;
         }
      }

      void upd(int ql, int qr, ll val, int l, int r, int x) {
         lz_upd(l, r, x);
         if (l > qr || r < ql) return;
         if (l >= ql && r <= qr) {
            seg[x] += 1ll * (r - l + 1) * val;
            if (l != r)
            {
               lz[x + x + 1] += val;
               lz[x + x + 2] += val;
            }
            return;
         }
         int mid = (l + r)/2;
         upd(ql, qr, val, l, mid, x + x + 1);
         upd(ql, qr, val, mid + 1, r, x + x + 2);
         seg[x] = seg[x + x + 1] + seg[x + x + 2];
      }

      ll get (int ql, int qr, int l, int r, int x) {
         lz_upd(l, r, x);
         if (l > qr || r < ql) return 0;
         if (l >= ql && r <= qr) return seg[x];

         int mid = (l + r)/2;
         ll lq = get(ql, qr, l, mid, x + x + 1);
         ll rq = get(ql, qr, mid + 1, r, x + x + 2);
         return lq + rq;
      }

      void update_range (int ql, int qr, ll val) {
         upd(ql, qr, val, 0, sz - 1, 0);
      }

      ll query_range_sum (int ql, int qr) {
         return get (ql, qr, 0, sz - 1, 0);
      }
}; /*}}}*/

signed main() {
   IOS; PREC;
   const int N = (int)1e6 + 10;
   int tc;
   cin >> tc;
   int n, A[N];
   fr (t, 1, tc) {
     cout << "Case #" << t << ": ";
     cin >> n;
     int mx = INT_MIN;
     fr (i, 0, n-1) cin >> A[i], mx = max(mx, A[i]);
     mx = max(n + 1, mx);

     seg_sum Tree(mx + 1);

     int last = 0;
     fr (i, 0, n-1) {
       Tree.update_range(1, A[i], 1);
       int get = Tree.query_range_sum(last + 1, last + 1);
       if (get >= last + 1){
         cout << last + 1 << ' ';
         last = last + 1;
       }
       else cout << last << ' ';
     }
     cout << '\n';
   }

   return EXIT_SUCCESS;
}

