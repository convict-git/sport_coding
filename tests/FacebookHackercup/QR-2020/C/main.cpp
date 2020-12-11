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

const int Maxn = 1e6 + 10;
typedef long long ll;
int N;
ll dp[Maxn];
int xPos[Maxn], yHeight[Maxn];
vector <ll> cordComp;

void preproc()
{
}

void solve()
{
   cordComp.clear();

   // take input
   cin >> N;

   for (int i = 0; i < N; ++i) {
      cin >> xPos[i] >> yHeight[i];
      cordComp.push_back(xPos[i]);
      cordComp.push_back(xPos[i] - yHeight[i]);
      cordComp.push_back(xPos[i] + yHeight[i]);
   }

   vector <int> isom(N);
   iota(isom.begin(), isom.end(), 0);
   sort(isom.begin(), isom.end(), [&] (int p, int q) {
         return xPos[p] + yHeight[p] < xPos[q] + yHeight[q]; });

   // Do the compression
   sort(cordComp.begin(), cordComp.end());
   cordComp.erase(
         unique(cordComp.begin(), cordComp.end()),
         cordComp.end());

   // compression map
   auto getIdxMap = [&] (ll pos) -> int {
      int idx = (int) (upper_bound(
               cordComp.begin(), cordComp.end(), pos) - cordComp.begin());
      return idx - 1;
   };

   int __N = static_cast <int> (cordComp.size());

   for (int i = 0; i <= __N; ++i) {
      dp[i] = 0;
   }

   ll mxRes = 0;

   for (int ii = 0; ii < N; ++ii) {
      int i = isom[ii];
      int lIdx = getIdxMap(xPos[i] - yHeight[i]);
      int cIdx = getIdxMap(xPos[i]);
      int rIdx = getIdxMap(xPos[i] + yHeight[i]);

      if (i != 0) {
         dp[rIdx] = max(dp[rIdx], dp[cIdx] + yHeight[i]);
         dp[cIdx] = max(dp[cIdx], dp[lIdx] + yHeight[i]);
      }
      else {
         dp[lIdx] = 0;
         dp[cIdx] = yHeight[i];
         dp[rIdx] = yHeight[i];
      }
      mxRes = max({mxRes, dp[lIdx], dp[cIdx], dp[rIdx]});
   }
   cout << mxRes << '\n';
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
