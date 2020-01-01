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
#define X         first
#define Y         second
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
   int operator () (pii x) const { return x.X*31 + x.Y; }
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

class seg_less { /*{{{*/
  // Recurisve Segment Tree with lazy propogation for "less than" library
  // This library is created by Priyanshu Shrivastav (mr.convict)
  // https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/segment_tree_less.cpp
  using ll = long long;
  public:
    struct Node {
      int sz;
      int *v;

      void update_node(Node left, Node right) {
        assert (sz == left.sz + right.sz);
        for (int i = 0; i < left.sz; ++i) v[i] = left.v[i];
        for (int i = 0; i < right.sz; ++i) v[i + left.sz] = right.v[i];
        sort (v, v + sz);
      }

      void add_val (int x) {
        for (int i = 0; i < sz; ++i) v[i] += x;
      }

      int get (int x) { // count of numbers strictly less than x
        int l = 0, h = sz - 1;
        while (l <= h) {
          int g = (l + h)/2;
          if (v[g] < x) l = g + 1;
          else h = g - 1;
        }
        return h + 1;
      }
    };

    seg_less (int n, int Ar[] = nullptr) {
      sz = n;
      if (Ar == nullptr)
        memset(ar, 0, sizeof(ar));
      else for (int i = 0; i < sz; ar[i] = Ar[i], ++i);
      create(0, n - 1, 0);
    }

    seg_less(int n, vector <int> Ar) {
      sz = n;
      assert((int)Ar.size() == n);
      for (int i = 0; i < sz; ar[i] = Ar[i], ++i);
      create(0, n - 1, 0);
    }

    static const int MXN = (int)2e5 + 10;
    int sz;
    int ar[MXN];
    Node seg[4 * MXN];
    int lz[4 * MXN];

    void create (int l, int r, int x) {
      seg[x].sz = r - l + 1;
      seg[x].v = new int [seg[x].sz];

      if (l == r)
      {
        seg[x].v[0] = ar[l];
        return;
      }
      int mid = (l + r)/2;
      create(l, mid, x + x + 1);
      create(mid + 1, r, x + x + 2);
      seg[x].update_node(seg[x + x + 1], seg[x + x + 2]);
    }

    void lz_upd(int l, int r, int x) {
      if (lz[x] != 0) {
        seg[x].add_val(lz[x]);

        if (l != r)
        {
          lz[x + x + 1] += lz[x];
          lz[x + x + 2] += lz[x];
        }
        lz[x] = 0;
        return;
      }
    }

    void upd(int ql, int qr, int val, int l, int r, int x) {
      lz_upd(l, r, x);
      if (l > qr || r < ql) return;
      if (l >= ql && r <= qr) {
        seg[x].add_val(val);

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
      seg[x].update_node(seg[x + x + 1], seg[x + x + 2]);
    }

    int get (int ql, int qr, int l, int r, int x, int limit) {
      lz_upd(l, r, x);
      if (l > qr || r < ql) return 0;
      if (l >= ql && r <= qr) return seg[x].get(limit);

      int mid = (l + r)/2;
      int lq = get(ql, qr, l, mid, x + x + 1, limit);
      int rq = get(ql, qr, mid + 1, r, x + x + 2, limit);
      return lq + rq;
    }

    void update_range (int ql, int qr, int val) {
      upd(ql, qr, val, 0, sz - 1, 0);
    }

    int query_range_less (int ql, int qr, int limit) {
      return get (ql, qr, 0, sz - 1, 0, limit);
    }
}; /*}}}*/

signed main() {
   // IOS; PREC;
   // freopen("input1", "r", stdin);
   // freopen("out.txt", "w", stdout);

   int n, k;
   cin >> n >> k;

   vi a(n);
   fr (i, 0, n - 1) cin >> a[i];

   const int D = 21, MAXN = 1e5 + 10;
   vvi bin(n, vi(D + 1, -1));

   int last[MAXN];
   fill(last, last + MAXN, -1);
   fr (i, 0, n - 1) {
     bin[i][0] = last[a[i]];
     last[a[i]] = i;
   }

   vi b(n);
   fr(i, 0, n-1) {
     fr (d, 1, D) if (bin[i][d - 1] != -1)
       bin[i][d] = bin[bin[i][d - 1]][d - 1];

     b[i] = i;
     fr (d, 0, D) if ((k & (1 << d)) && b[i] >= 0)
       b[i] = bin[b[i]][d];
   }

   seg_less Tree(n, b);

   int q, lst = 0;
   cin >> q;
   while (q--) {
     int l, r;
     cin >> l >> r;
     l = (l + lst) % n;
     r = (r + lst) % n;

     if (l > r) swap(l, r);
     lst = Tree.query_range_less(l, r, l);
     cout << lst << '\n';
   }

   return EXIT_SUCCESS;
}

