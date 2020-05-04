#include <bits/stdc++.h>
using namespace std;

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
  vector <vector <int>> fsm(n + 1, vector <int> (26));
  vector <int> pi = pref_func(t);
  for (int len = 0; len <= n; ++len) {
    for (int ch = 0; ch < 26; ++ch) {
      if (len == 0 || t[len] == char('a' + ch))
        fsm[len][ch] = len + (t[len] == char('a' + ch));
      else
        fsm[len][ch] = fsm[pi[len - 1]][ch];
    }
  }
  return fsm;
}
