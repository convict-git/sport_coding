#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

// Recursive Segment Tree with lazy propogation for "less than" library
// This library is created by Priyanshu Shrivastav (mr.convict)
// https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/segment_tree_less.cpp

template <class __T = int>
class Node {
  public:
    vector <pair <__T, int>> v;

    void init_node(int l, const __T &x) {
      v.push_back(make_pair(x, l));
    }

    void merge(const Node &left, const Node &right) {
      v.clear();
      v.insert(v.begin(), left.v.begin(), left.v.end());
      v.insert(v.begin() + left.v.size(), right.v.begin(), right.v.end());
      sort(v.begin(), v.end());
    }

    void add_val (const __T &x) {
      for (auto &el : v) el.first += x;
    }

    int get (const __T &x) {
      int l = 0, h = (int)v.size() - 1;
      while (l <= h) {
        int g = (l + h)/2;
        if (v[g].first <= x) l = g + 1;
        else h = g - 1;
      }
      return h + 1;
    }
};

template <class __S = int>
class binop  {
   public:
  static const __S base_case = 0; // numeric_limits <__S>::min();
  __S operator () (const __S &x, const __S &y)  {
    return x + y; // max(x, y);
  }
};

template <class __T = long long, class __S = __T, class __F = binop <__S>>
class seg_less {
  public:
    int sz;
    vector <__T> ar;
    vector <Node <__T>> seg;
    vector <__T> lz;

    seg_less(int n, const vector <__T> &Ar) {
      assert((int)Ar.size() == n);

      sz = n;
      seg.assign(4 * n, Node <__T>());
      lz.assign(4 * n, 0);
      ar.insert(ar.begin(), Ar.begin(), Ar.end());
      create(0, n - 1, 0);
    }

    void create (int l, int r, int x) {
      if (l == r)
      {
        seg[x].init_node(l, ar[l]);
        return;
      }
      int mid = (l + r)/2;
      create(l, mid, x + x + 1);
      create(mid + 1, r, x + x + 2);
      seg[x].merge(seg[x + x + 1], seg[x + x + 2]);
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

    __S get (int ql, int qr, int l, int r, int x, const __T &limit) {
      lz_upd(l, r, x);
      if (l > qr || r < ql) return __F::base_case;
      if (l >= ql && r <= qr) return seg[x].get(limit);

      int mid = (l + r)/2;
      __S lq = get(ql, qr, l, mid, x + x + 1, limit);
      __S rq = get(ql, qr, mid + 1, r, x + x + 2, limit);
      return __F() (lq, rq);
    }

    __S query_range_less (int ql, int qr, const __T &limit) {
      assert(ql >= 0 && qr <= sz - 1);
      return get (ql, qr, 0, sz - 1, 0, limit);
    }
};

void preproc()
{
}

typedef long long Int;

void solve()
{
   int N;
   cin >> N;
   vector <pair <int ,int>> arp(N);
   for (int i = 0; i < N; ++i) {
      cin >> arp[i].first;
      arp[i].second = i + 1;
   }
   sort(arp.begin(), arp.end());
   vector <Int> ar(N);
   for (int i = 0; i < N; ++i) { ar[i] = arp[i].second; }
   debug(arp);
   seg_less <Int> st(N, ar);

   Int ans = 0;
   for (int i = 0; i < N; ++i) {
      // (value, idx (1 based))
      // find the left range value
      int L = 0, H = N - 1;
      while (L <= H) {
         int g = (L + H) / 2;
         if (arp[g].first < arp[i].second) { L = g + 1; }
         else { H = g - 1; }
      }
      Int getCnt = st.query_range_less(L, N - 1, arp[i].first);
      ans += getCnt;
      debug(i, arp[i].second, getCnt);
      if (arp[i].first >= arp[i].second) ans -= 1;
   }
   cout << ans / 2 << '\n';
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
