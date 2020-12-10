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
   int N;
   cin >> N;
   // go for a N^2 solution if needed
   vector <int> ar(N);
   vector <int> occ(N+1);

   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
      occ[ar[i]]++;
   }
   set <int, greater <int>>S;
   for (int i = 0; i <= N; ++i) {
      if (!occ[i]) S.insert(i);
   }
   int mx = *max_element(ar.begin(), ar.end());

   vector <int> resIdx;
   for (int i = N-1; i >= 0; --i) {
      debug(i, ar[i], mx);
      if (ar[i] > mx) {
         if (S.empty()) {
            assert(false);
         }
         else {
            int notUsed = *S.begin();
            debug(notUsed);
            S.erase(S.begin());
            --occ[ar[i]];
            if (occ[ar[i]] == 0) {
               S.insert(ar[i]);
            }
            ar[i] = notUsed;
            ++occ[ar[i]];
            resIdx.push_back(i + 1);
         }
      }
      mx = ar[i];
   }
   cout << resIdx.size() << '\n';
   for (int idx : resIdx) {
      cout << idx << ' ';
   }
   cout << '\n';
}

signed main() {
  IOS; PREC;
  preproc();
  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    cerr << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}

