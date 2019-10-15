#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e6 + 10;
int pi[N];
int fsm[26][N];

void pref_func (string &s) {
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
}

void calc_fsm(string t) {
   t += '#';
   int sz = (int)t.size();
   pref_func(t);

   for (int len = 0, j; len < sz; ++len) {
      for (int ch = 0; ch < 26; ++ch) {
         if (len > 0 && t[len] !=  char('a' + ch)) {
            fsm[ch][len] = fsm[ch][pi[len - 1]];
         }
         else {
            fsm[ch][len] = len + (t[len] == char('a' + ch));
         }
      }
   }
}

