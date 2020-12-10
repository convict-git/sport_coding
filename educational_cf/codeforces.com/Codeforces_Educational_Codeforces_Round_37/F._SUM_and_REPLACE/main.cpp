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

const int mxn = 1e6;
vector <int> dv(mxn+1);

void preproc() {
   for (int i = 1; i <= mxn; ++i) {
      for (int j = 0; j <= mxn; j += i) {
         ++dv[j];
      }
   }
}

vector <long long> sg;
vector <int> qry_seen;
vector <int> ar;

void create (int l, int r, int x) {
   if (l == r) {
      sg[x] = ar[l];
      qry_seen[x] = 0;
      return;
   }
   int mid = (l + r) / 2;
   create(l, mid, x + x + 1);
   create(mid + 1, r, x + x + 2);
   sg[x] = sg[x + x + 1] + sg[x + x + 2];
}

void upd (int ql, int qr, int l, int r, int x) {
   if (l > qr || r < ql)  // outside
      return;
   if (l == r) {
      sg[x] = dv[sg[x]];
      qry_seen[x] += 1;
      return;
   }
   if (qry_seen[x] > 6) {
      return;
   }
   if (l >= ql && r <= qr) {
      qry_seen[x] += 1;
   }
   int mid = (l + r) / 2;
   upd(ql, qr, l, mid, x + x + 1);
   upd(ql, qr, mid + 1, r, x + x + 2);
   sg[x] = sg[x + x + 1] + sg[x + x + 2];
}

long long get (int ql, int qr, int l, int r, int x) {
   if (l > qr || r < ql) return 0;
   if (l >= ql && r <= qr)
      return sg[x];
   int mid = (l + r) / 2;
   return get(ql, qr, l, mid, x + x + 1)
      + get(ql, qr, mid+1, r, x + x + 2);
}

void solve() {
   int n, m;
   cin >> n >> m;
   ar.assign(n, 0);
   sg.assign(4 * n, 0);
   qry_seen.assign(4 * n, 0);
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
   }
   create(0, n - 1, 0);
   while (m--) {
      int l, r, k;
      cin >> k >> l >> r;
      --l, --r;
      if (k == 1)  { // replace
         upd(l, r, 0, n - 1, 0);
      }
      else { // sum
         cout << get(l, r, 0, n - 1, 0) << '\n';
      }
   }
}

signed main() {
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
