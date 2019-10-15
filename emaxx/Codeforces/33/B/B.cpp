#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;

const int infi = (int)1e9;
int W[26][26];

void floydWarshall () {
   for(int k = 0; k < 26; ++k)
      for (int i = 0; i < 26; ++i)
         for (int j = 0; j < 26; ++j)
            if (W[i][k] < infi && W[k][j] < infi)
               W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
}

signed main() {
   IOS; PREC;
   string s1, s2;

   for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < 26; ++j) {
         W[i][j] = (i == j ? 0 : infi);
      }
   }
   cin >> s1 >> s2;
   int m, w;
   cin >> m;
   char a, b;
   while (m--) {
      cin >> a >> b >> w;
      W[a - 'a'][b - 'a'] = min(w, W[a - 'a'][b - 'a']);
   }
   floydWarshall();

   if (s1.size() != s2.size()) cout << -1 << '\n';
   else {
      int totalCost = 0;
      string ans = s1;
      for (int i = 0; i < (int)s1.size(); ++i) {
      a = s1[i], b = s2[i];
         int mn = infi;
         for (int j = 0; j < 26; ++j) {
            if (W[a - 'a'][j] < infi && W[b - 'a'][j] < infi)
               if (mn > W[a - 'a'][j] + W[b - 'a'][j]) {
                  mn = W[a - 'a'][j] + W[b - 'a'][j];
                  ans[i] = char (j + 'a');
               }
         }
         if (mn == infi) {
            cout << -1 << '\n';
            return 0;
         }
         totalCost += mn;
      }
      cout << totalCost << '\n';
      cout << ans << '\n';
   }

   return EXIT_SUCCESS;
}
