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
