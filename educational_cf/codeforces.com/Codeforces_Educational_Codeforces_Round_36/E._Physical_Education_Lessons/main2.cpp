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

void preproc() {
}

void solve() {
   int n, q;
   cin >> n >> q;

   struct obj {
      int L, R;
      bool operator < (const obj &o) const {
         return R < o.R;
      };
   };
   set <obj> s;
   int cnt = n;

   while (q--) {
      int L, R, K;
      cin >> L >> R >> K;
      int nwzero = 0;
      vector <set <obj>::iterator> ersv;
      vector <obj> insv;
      bool ins = true;
      if (!s.empty()) {
         auto it = lower_bound(s.begin(), s.end(), obj({-1, L})); // find basis on L
         if (K == 1) {
            for (; it != s.end(); ++it) { // remove all those which overlaps
               int cL = it->L, cR = it->R;
               if (cL <= L && cR >= R) { // no help or update
                  ins = false;
                  break;
               }
               else if (cL <= L && cR <= R) {
                  ersv.push_back(it);
                  nwzero += L - cL;
                  L = cL;
               }
               else if (cL >= L && cR <= R) { // merge
                  ersv.push_back(it);
                  nwzero += (cL - L) + (R - cR);
               }
              else if (cL <= R) { // merge
                  ersv.push_back(it);
                  nwzero += cR - R;
                  R = cR;
               }
               else { // add
                  nwzero += R - L + 1;
                  break;
               }
            }
         }
         else {
            ins = false;
            for (; it != s.end(); ++it) {
               int cL = it->L, cR = it->R;
               if (cL >= R) { // no help
                  break;
               }
               else if (cL <= L && cR >= R) {
                  ersv.push_back(it);
                  if (cL <= L - 1)
                     insv.push_back({cL, L - 1});
                  if (R + 1 <= cR)
                     insv.push_back({R + 1, cR});
                  nwzero -= R - L + 1;
                  break;
               }
               else if (cL >= L && cR >= R) {
                  ersv.push_back(it);
                  nwzero -= R - cL + 1;
                  break;
               }
               else if (cL >= L && cR <= R) {
                  ersv.push_back(it);
                  nwzero -= cR - cL + 1;
               }
               else {
                  ersv.push_back(it);
                  nwzero -= cR - L;
                  if (L - 1 >= cL)
                     insv.push_back({cL, L - 1});
               }
            }
         }
      }
      for (auto el : ersv) {
         s.erase(el);
      }
      for (auto el : insv) {
         s.insert(el);
      }
      if (ins) s.insert({L, R});
      cnt -= nwzero;
      cout << cnt << '\n';
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
