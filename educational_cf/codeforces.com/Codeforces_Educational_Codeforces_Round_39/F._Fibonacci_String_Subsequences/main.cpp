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

vector <int> pref_func (string &s) { // O(|s|)
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

// each state represents prefix length
// transition : length * char -> length
vector <vector <int>> calc_fsm(string t) { // O(|s| * 26)
  int n = (int)t.size();
  t += '#';
  vector <vector <int>> fsm(n + 1, vector <int> (2));
  vector <int> pi = pref_func(t);
  for (int len = 0; len <= n; ++len) {
    for (int ch = 0; ch < 2; ++ch) {
      if (len == 0 || t[len] == char('0' + ch))
        fsm[len][ch] = len + (t[len] == char('0' + ch));
      else
        fsm[len][ch] = fsm[pi[len - 1]][ch];
    }
  }
  return fsm;
}

const int Mxn = 1e2 + 10;
const int Mod = 1e9 + 7;
int N, X;
string s;
int G[Mxn][Mxn], K[Mxn][Mxn];
vector <vector <int>> fsm;

void preproc() {
}

void solve() {
   cin >> N >> X >> s;
   fsm = calc_fsm(s);

   for (int j = 0; j <= N; ++j) {
      G[0][j] = fsm[j][0];
      K[0][j] = (G[0][j] == N);
      G[1][j] = fsm[j][1];
      K[1][j] = (G[1][j] == N);
   }

   for (int i = 2; i <= X; ++i) {
      for (int j = 0; j <= N; ++j) {
         int k = G[i - 1][j];
         G[i][j] = G[i - 2][k];
         K[i][j] = (K[i - 1][j] + K[i - 2][k]) % Mod;
      }
   }
   cout << K[X][0] << '\n';
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
