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
//

const int N = (int)2e5 + 10;
int seg[4 * N];
void create (int l, int r, int x, vi &A) {
   if (l == r) {
      seg[x] = A[l];
      return;
   }
   int mid = (l+r)/2;
   create(l, mid, x + x + 1, A);
   create(mid+1, r, x + x + 2, A);
   seg[x] = min(seg[x + x + 1], seg[x + x + 2]);
}

int query (int l, int r, int x, int ql, int qr, int m) {
   if (l > qr || r < ql) return m+1;
   if (l >= ql && r <= qr) return seg[x];
   int mid = (l+r)/2;
   int lq = query(l, mid, x + x + 1, ql, qr, m);
   int rq = query(mid+1, r, x + x + 2, ql, qr, m);
   return min(lq, rq);
}

signed main() {
   IOS; PREC;

   const int D = 21;
   int n, m, q;
   cin >> n >> m >> q;
   vi p(n), A(m);
   vvi table(m, vi(D+1, m+1));
   fr(i, 0, n-1) cin >> p[i];
   fr(i, 0, m-1) cin >> A[i];

   vi nxt(n+1, -1);
   fr(i, 0, n-2) nxt[p[i]] = p[i+1];
   nxt[p[n-1]] = p[0];

   vi recent_idx(n+1, m+1);
   fR(i, m-1, 0) {
      table[i][0] = recent_idx[nxt[A[i]]];
      recent_idx[A[i]] = i;
   }

   fr(k, 1, D) fR(i, m-1, 0)
      if (table[i][k-1] < m)
         table[i][k] = table[table[i][k-1]][k-1];

   vi idx(m, m+1);
   fr(i, 0, m-1) {
      int j = i;
      for (int d = 0; d <= D && j < m; ++d)
         if ((1 << d) & (n-1)) j = table[j][d];
      idx[i] = j;
   }

   create(0, m-1, 0, idx);

   while (q--) {
      int l, r;
      cin >> l >> r;
      --l, --r;
      int r_min_idx = query (0, m-1, 0, l, r, m);
      if (r_min_idx <= r) cout << "1";
      else cout << "0";
   }
   cout << '\n';
   return EXIT_SUCCESS;
}

