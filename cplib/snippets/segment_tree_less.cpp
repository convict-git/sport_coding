#include <bits/stdc++.h>
using namespace std;

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

    int get (const __T &x) { // count of numbers strictly less than x
      int l = 0, h = (int)v.size() - 1;
      while (l <= h) {
        int g = (l + h)/2;
        if (v[g].first < x) l = g + 1;
        else h = g - 1;
      }
      return h + 1;
    }
};

template <class __S = int>
class binop  {
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

    void upd (int ql, int qr, const __T &val, int l, int r, int x) {
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
      seg[x].merge(seg[x + x + 1], seg[x + x + 2]);
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

    void update_range (int ql, int qr, const __T &val) {
      upd(ql, qr, val, 0, sz - 1, 0);
    }

    __S query_range_less (int ql, int qr, const __T &limit) {
      assert(ql >= 0 && qr <= sz - 1);
      return get (ql, qr, 0, sz - 1, 0, limit);
    }
};

