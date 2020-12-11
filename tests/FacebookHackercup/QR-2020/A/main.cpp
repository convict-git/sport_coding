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

int N;
int W[52][52];

void preproc()
{
}

void solve()
{
   cin >> N;
   string In, Out;
   cin >> In >> Out;

   // intialize
   for(int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
         W[i][j] = false;
      }
      if (i) {
         W[i - 1][i] = W[i][i - 1] = true;
      }
      if (i < N - 1) {
         W[i + 1][i] = W[i][i + 1] = true;
      }
   }

   // add constraints
   for (int i = 0; i < N; ++i) {
      if (In[i] == 'N') {
         for (int j = 0; j < N; ++j) {
            W[j][i] = false;
         }
      }
      if (Out[i] == 'N') {
         for (int j = 0; j < N; ++j) {
            W[i][j] = false;
         }
      }
      W[i][i] = true;
   }

   // warshall's
   for (int k = 0; k < N; ++k) {
      for (int i = 0; i < N; ++i) {
         for (int j = 0; j < N; ++j) {
            W[i][j] |= W[i][j] or (W[i][k] and W[k][j]);
         }
      }
   }

   for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
         cout << (W[i][j] ? 'Y' : 'N');
      }
      cout << '\n';
   }
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    cout << "Case #" << Tt << ":\n";
    solve();
  }
  return EXIT_SUCCESS;
}
