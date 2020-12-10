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

void preproc()
{
}

void solve()
{
   vector <int> L(3);
   vector <int> C(3);
   for (int i = 0; i < 3; ++i) cin >> L[i];
   for (int i = 0; i < 3; ++i) cin >> C[i];

   int N, A, B;
   cin >> N >> A >> B;

   if (A > B) swap(A, B);
   vector <long long> dist(N + 1);
   for (int i = 2; i <= N; ++i) {
      cin >> dist[i];
   }

   // binary search to get the max index satisfying dist between pos and
   // nxt_pos to be <= mx_len
   const int D = 17;
   auto give_mxidx = [&] (int pos, int mx_len) -> int {
      int nxt_pos = pos;
      for (int k = D; k >= 0; --k) {
         if (nxt_pos + (1 << k) - 1 <= N and
               dist[nxt_pos + (1 << k) - 1] - dist[pos] <= mx_len) {
            nxt_pos += (1 << k);
         }
      }
      return nxt_pos - 1;
   };

   vector <bool> vis(N);
   using pp = pair <long long, int>;
   priority_queue <pp, vector <pp>, greater <pp>> pq;

   pq.push({0, A});

   while (!pq.empty()) {
      long long len = pq.top().first;
      int pos = pq.top().second;
      pq.pop();

      if (vis[pos]) continue;
      vis[pos] = true;

      if (pos >= B) {
         cout << len << '\n';
         return;
      }

      // try all L1, L2, L3
      for (int rot = 0; rot < 3; ++rot) {
         int nxt_pos = give_mxidx (pos, L[rot]);
         if (!vis[nxt_pos]) {
            pq.push(make_pair(len + C[rot], nxt_pos));
         }
      }
   }
   assert(false);
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
