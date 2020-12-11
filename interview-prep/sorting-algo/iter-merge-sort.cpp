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
void merge (int idx1, int len1, int idx2, int len2,
      vector <int> &Ar)
{
   vector <int> temp;
   int i = idx1, j = idx2;
   while (i <= idx1 + len1 - 1 and j <= idx2 + len2 - 1) {
      if (Ar[i] < Ar[j]) temp.push_back(Ar[i++]);
      else temp.push_back(Ar[j++]);
   }
   if (j == idx2 + len2) {
      while (i <= idx1 + len1 - 1)
         temp.push_back(Ar[i++]);
   }
   if (i == idx1 + len1) {
      while (j <= idx2 + len2 - 1)
         temp.push_back(Ar[j++]);
   }

   int k = 0;
   for (i = idx1; i <= idx1 + len1 - 1; ++i) {
      Ar[i] = temp[k++];
   }
   for (i = idx2; i <= idx2 + len2 - 1; ++i) {
      Ar[i] = temp[k++];
   }
}

void solve()
{
   // iterative merge sort
   int N;
   cin >> N;
   vector <int> Ar(N);
   for (int &a : Ar) cin >> a;

   for (int len = 1; len < N; len *= 2) {
      for (int i = 0; i + len < N; i += 2 * len) {
         int idx1 = i, len1 = len;
         int idx2 = i + len, len2 = min(N - (i + len) + 1, len);
         merge(idx1, len1, idx2, len2, Ar);
      }
   }

   for (int &a : Ar) cout << a << ' ';
   cout << '\n';
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
