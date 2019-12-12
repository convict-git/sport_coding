#include <bits/stdc++.h>
using namespace std;

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

