#include <bits/stdc++.h>
using namespace std; class seg_min {
   public:
      using ll = long long;
      seg_min (int n, int Ar[] = nullptr) {
         sz = n;
         if (Ar == nullptr)
            memset(ar, 0, sizeof(ar));
         else for (int i = 0; i < sz; ar[i] = Ar[i], ++i);
         create(0, n - 1, 0);
      }

      static const int MXN = (int)2e5 + 10;
      static const ll inf = (ll)1e18;
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
         int mid = (l + r) >> 1;
         create(l, mid, x + x + 1);
         create(mid + 1, r, x + x + 2);
         seg[x] = min(seg[x + x + 1], seg[x + x + 2]);
      }

      void lz_upd(int l, int r, int x) {
         if (lz[x] != 0) {
            seg[x] += lz[x];
            if (l != r)
            {
               lz[x + x + 1] += lz[x];
               lz[x + x + 2] += lz[x];
            }
            lz[x] = 0;
            return;
         }
      }
      void update_min (int ql, int qr, ll val) {
         upd(ql, qr, val, 0, sz - 1, 0);
      }

      ll query_min (int ql, int qr) {
         return get (ql, qr, 0, sz - 1, 0);
      }

      void upd(int ql, int qr, ll val, int l, int r, int x) {
         lz_upd(l, r, x);
         if (l > qr || r < ql) return;
         if (l >= ql && r <= qr) {
            seg[x] += val;
            if (l != r)
            {
               lz[x + x + 1] += val;
               lz[x + x + 2] += val;
            }
            return;
         }
         int mid = (l + r) >> 1;
         upd(ql, qr, val, l, mid, x + x + 1);
         upd(ql, qr, val, mid + 1, r, x + x + 2);
         seg[x] = min(seg[x + x + 1], seg[x + x + 2]);
      }

      ll get (int ql, int qr, int l, int r, int x) {
         lz_upd(l, r, x);
         if (l > qr || r < ql) return inf;
         if (l >= ql && r <= qr) return seg[x];

         int mid = (l + r) >> 1;
         ll lq = get(ql, qr, l, mid, x + x + 1);
         ll rq = get(ql, qr, mid + 1, r, x + x + 2);
         return min(lq, rq);
      }
};
