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

typedef long long Int;
void preproc()
{ }

struct TrieNode {
   bool leafNode;
   TrieNode* nxtNodes[26];
   void init() { leafNode = false; memset(nxtNodes, 0, sizeof(nxtNodes)); }
   TrieNode* addChar(char ch) {
      if (nxtNodes[ch - 'a'] == nullptr) {
         nxtNodes[ch - 'a'] = new TrieNode;
         nxtNodes[ch - 'a']->init();
      }
      return nxtNodes[ch - 'a'];
   }
};

void solve()
{

   TrieNode* headPtr = new TrieNode;
   headPtr->init();
   string s;
   cin >> s;
   int N = (int)s.size();
   int K;
   cin >> K;
   for (int e = 0; e < K; ++e) {
      string tmp;
      cin >> tmp;
      TrieNode* curHead = headPtr;
      for (int i = 0; i < (int)tmp.size(); ++i) {
         curHead = curHead->addChar(tmp[i]);
      }
      curHead->leafNode = true;
   }
   vector <vector <int>> occ(N, vector <int> (N));

   for (int i = 0; i < N; ++i) {
      TrieNode* curHead = headPtr;
      for (int j = i; j < N; ++j) {
         curHead = curHead->nxtNodes[s[j] - 'a'];
         if (curHead == nullptr) { break; }
         if (curHead->leafNode == true) {
            occ[i][j] = true;
         }
      }
   }
   vector <int> dp(N + 1);
   vector <bool> vis(N + 1);
   dp[0] = 1;
   vis[0] = true;

   const int Mod = 1e9 + 7;
   // dp[i] += dp[j] and [i+1, j] is present as a in dict
   for (int i = 0; i <= N; ++i) {
      for (int j = i + 1; j <= N; ++j) {
         if (vis[i] and occ[i][j - 1] == true) {
            vis[j] = true;
            dp[j] += dp[i];
            dp[j] %= Mod;
         }
      }
   }
   cout << dp[N] << endl;
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
