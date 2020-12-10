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

// @ O(|s|)
vector <int> pref_func
(string &s)
{
  int n = (int)s.size();
  vector <int> pi(n);
   pi[0] = 0;
   int sz = (int)s.size();
   for (int i = 1; i < sz; ++i) {
      int len_j = pi[i-1];
      int j = len_j - 1;
      while (len_j > 0 && s[j + 1] != s[i]) {
         len_j = pi[j];
         j = len_j - 1;
      }
      if (s[len_j] == s[i])
         ++len_j;
      pi[i] = len_j;
   }
   return pi;
}

// @ each state represents prefix length
// @ transition : length * char -> length,  O(|s| * |alpha|)
vector <vector <int>> calc_fsm
(string t)
{
  int n = (int)t.size();
  const int AlpSz = 2;
  t += '#';
  vector <int> pi = pref_func(t);

  vector <vector <int>> fsm(n + 1, vector <int> (AlpSz));

  for (int len = 0; len <= n; ++len) {
    for (int ch = 0; ch < AlpSz; ++ch) {
      if (len == 0 || t[len] == char('0' + ch))
        fsm[len][ch] = len + (t[len] == char('0' + ch));
      else
        fsm[len][ch] = fsm[pi[len - 1]][ch];
    }
  }
  return fsm;
}

const int Mod = (int)1e9 + 7;
inline int add (int x, int y) { return (1ll * x + y + (Mod << 1)) % Mod; }
inline int sub (int x, int y) { return (1ll * x - y + (Mod << 1)) % Mod; }
inline int mul (int x, int y) { return (int) (1ll*(x + Mod) * (y + Mod) % Mod); }
inline int pow (int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = mul(res, x);
    x = mul(x, x), y >>= 1;
  }
  return res;
}
inline int inv (int x) { return pow(x, Mod - 2); }
inline int dv (int x, int y) { return mul(x, inv(y)); }

const int Maxn = 110;
int M[Maxn][Maxn][Maxn]; // M(i, j, k), ith F, starting from jth state reaching kth state
int lenS, xFibIdx;
string S;

// @ Brief Multiplies two matrices
void mulMatrices
(int toIdx,
 int fromFirstIdx,
 int fromSecondIdx)
{
   for (int st = 0; st <= lenS; ++st) { // start state
      for (int en = 0; en <= lenS; ++en) { // end state
         int& updM = M[toIdx][st][en], lft, rt;
         for (int mid = 0; mid <= lenS; ++mid) { // mid state
            lft = M[fromFirstIdx][st][mid];
            rt = M[fromSecondIdx][mid][en];
            updM = add(updM, mul(lft, rt));
         }
      }
   }
}

void showMat
(int idx)
{
   cerr << "Matrix : " << idx << endl;
   for (int st = 0; st <= lenS; ++st) {
      for (int en = 0; en <= lenS; ++en) {
         cerr << M[idx][st][en] << ' ';
      }
      cerr << '\n';
   }
}

void preproc()
{
}

void solve()
{
   memset(M, 0, sizeof(M));
   cin >> lenS >> xFibIdx >> S;
   vector <vector <int>> aut = calc_fsm(S);

   // initiate M[0] and M[1]
   // M[idx][st][st] = 1, st -> st, when you don't take a move
   for (int idx = 0; idx < 2; ++idx) {
      for (int st = 0; st <= lenS; ++st) {
         M[idx][st][st] = 1;
      }
   }

   // M[idx][st][aut[st][idx]]++ , st -> aut[st][idx], when you take a move
   for (int idx = 0; idx < 2; ++idx) {
      for (int st = 0; st <= lenS; ++st) {
         int nxtState = aut[st][idx];
         M[idx][st][nxtState] += 1;
      }
   }

   // M[idx] = M[idx-1] * M[idx - 2]
   for (int idx = 2; idx <= xFibIdx; ++idx) {
      mulMatrices(idx, idx - 1, idx - 2);
   }

   // Final answer is M[xFibIdx][0][lenS]
   cout << M[xFibIdx][0][lenS] << '\n';
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
