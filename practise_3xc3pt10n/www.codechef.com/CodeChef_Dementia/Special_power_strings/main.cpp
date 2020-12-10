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


const int Maxn = 610;
int dp[Maxn][Maxn];
string A, B;
int szA, szB;
vector <set <char>> setCor(3);
map <char, int> mp;

void preproc()
{
}

void solve()
{
   mp.clear();
   mp['#'] = 0, mp['?'] = 1, mp['!'] = 2;

   cin >> A >> B;
   szA = static_cast <int> (A.size());
   szB = static_cast <int> (B.size());

   A = '@' + A;
   B = '@' + B;

   string tmp;
   for (int i = 0; i < 3; ++i) {
      cin >> tmp;
      setCor[i].clear();
      for (char ch : tmp) setCor[i].insert(ch);
   }

   for (int i = 0; i <= szB; ++i) {
      for (int j = 0; j <= szA; ++j) {
         dp[i][j] = INT_MAX;
      }
   }
   dp[0][0] = 0;

   for (int i = 1; i <= szB; ++i) {
      for (int j = 1; j <= szA; ++j) {
         // if it is not possible to update future states then continue
         if (dp[i - 1][j - 1] == INT_MAX) {
            continue;
         }
         // if special power charac
         if (mp.find(B[i]) != mp.end()) {
            int idx = mp.at(B[i]); // which char hash, ques, excl
            dp[i][j - 1] = min(dp[i][j - 1], dp[i - 1][j - 1]); // do not use the char

            for (int k = j; k <= szA; ++k) {
               if (setCor[idx].find(A[k]) == setCor[idx].end()) {
                  break;
               }
               dp[i][k] = min(dp[i][k], dp[i - 1][j - 1] + 1);
            }
         }
         // otherwise has to be equal
         else if (B[i] == A[j]) {
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
         }
         // not equal
         else {
            // do nothing
         }
      }
   }

   cout << (dp[szB][szA] == INT_MAX ? -1 : dp[szB][szA]) << '\n';
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
