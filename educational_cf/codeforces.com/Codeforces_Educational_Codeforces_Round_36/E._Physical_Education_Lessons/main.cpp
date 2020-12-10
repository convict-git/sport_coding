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

#include <bits/stdc++.h>
using namespace std;

vector <int> sg;
vector <int> lz;
vector <int> idx;
 // 2 is for putting all 1, 1 is for putting all 0
void lzupd(int l, int r, int x) {
   if (lz[x] != 0)  {
      sg[x] = (lz[x] == 2 ? idx[r] - idx[l] + 1 : 0);
      if (l != r) {
         lz[x + x + 1] = lz[x];
         lz[x + x + 2] = lz[x];
      }
      lz[x] = 0;
   }
}

void upd (int ql, int qr, int l, int r, int x, int ktype) {
   lzupd(l, r, x);
   if (l > qr || r < ql) return;
   if (l >= ql && r <= qr) {
      sg[x] = (ktype == 2 ? idx[r] - idx[l] + 1 : 0);
      if (l != r) {
         lz[x + x + 1] = lz[x + x + 2] = ktype;
      }
      return;
   }
   int mid = (l + r) / 2;
   upd(ql, qr, l, mid, x + x + 1, ktype);
   upd(ql, qr, mid + 1, r, x + x + 2, ktype);
   sg[x] = sg[x + x + 1] + sg[x + x + 2];
}

int get (int ql, int qr, int l, int r, int x) {
   lzupd(l, r, x);
   if (l > qr || r < ql) {
      return 0;
   }
   if (l >= ql && r <= qr) {
      return sg[x];
   }
   int mid = (l + r) / 2;
   return get(ql, qr, l, mid, x + x + 1) + get(ql, qr, mid + 1, r, x + x + 2);
}

void preproc() {
}

void solve() {
   int n, q;
   cin >> n >> q;
   struct query {
      int L, R, K;
   };
   vector <query> qry(q);
   for (int i = 0; i < q; ++i) {
      cin >> qry[i].L >> qry[i].R >> qry[i].K;
      idx.push_back(qry[i].L);
      idx.push_back(qry[i].L + 1);
      idx.push_back(qry[i].L + 2);
      idx.push_back(qry[i].R);
      idx.push_back(qry[i].R + 1);
      idx.push_back(qry[i].R + 2);
   }
   idx.push_back(1);
   idx.push_back(n);
   sort(idx.begin(), idx.end());
   idx.erase(unique(idx.begin(), idx.end()), idx.end());

   auto give_idx = [&] (int x) -> int {
      return (int)(lower_bound(idx.begin(), idx.end(), x) - idx.begin());
   };
   debug(idx);

   int mxn = (int)idx.size();
   sg.assign(4 * mxn, 0);
   lz.assign(4 * mxn, 0);
   int low = give_idx(1), high = give_idx(n);
   upd(low, high, 0, mxn - 1, 0, 2);
   for (int i = 0; i < q; ++i) {
      int l = give_idx(qry[i].L), r = give_idx(qry[i].R);
      debug(l, r, qry[i].K);
      upd(l, r, 0, mxn - 1, 0, qry[i].K);
      cout << get(low, high, 0, mxn - 1, 0) << '\n';
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
