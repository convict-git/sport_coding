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

long long fac[20];
int ar[30], A[20], B[20];
map <long long, int> mpA[30], mpB[30];

void preproc()
{
   fac[0] = 1;
   for (int i = 1; i < 20; ++i)
      fac[i] = fac[i - 1] * i;
}

void recA (int idx, int N1, int k, long long s) { // first segment
   if (idx == N1) {
      // store the answer
      mpA[k][s]++;
      return;
   }

   recA(idx + 1, N1, k, s); // dont take it
   recA(idx + 1, N1, k, s + A[idx]); // take simply
   if (A[idx] <= 18) { // take factorial
      recA(idx + 1, N1, k + 1, s + fac[A[idx]]);
   }
   return;
}

void recB (int idx, int N2, int k, long long s) { // second segment
   if (idx == N2) {
      mpB[k][s]++;
      return;
   }

   recB(idx + 1, N2, k, s);
   recB(idx + 1, N2, k, s + B[idx]);
   if (B[idx] <= 18) {
      recB(idx + 1, N2, k + 1, s + fac[B[idx]]);
   }
}

void solve()
{
   int N, K;
   long long S;
   cin >> N >> K >> S;
   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
   }
   int N1 = N/2, N2 = N - N/2;
   for (int i = 0; i < N1; ++i) {
      A[i] = ar[i];
   }
   for (int i = 0; i < N2; ++i) {
      B[i] = ar[i + N1];
   }

   recA(0, N1, 0, 0);
   recB(0, N2, 0, 0);

   long long res = 0;

   for (int i = 0; i <= K; ++i) { // now we have atmost k - i left
      for (auto val : mpA[i]) {
         for (int j = 0; j <= K - i; ++j) {
            if (mpB[j].find(S - val.first) != mpB[j].end()) {
               res += 1ll * val.second * mpB[j][S - val.first];
            }
         }
      }
   }
   cout << res << '\n';
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

