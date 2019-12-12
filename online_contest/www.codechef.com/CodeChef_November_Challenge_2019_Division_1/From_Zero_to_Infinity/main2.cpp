#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e6 + 10;
vector <string> S[2];
int xc[26], fxc[26];
int k;
long double ans = 0;

void calc () {
  for (int rot = 0; rot < 2; ++rot) {
    for (int i = 0; i < 26; ++i) xc[i] = fxc[i] = 0;
    k = (int)S[rot].size();

    for (string& s : S[rot]) {
      vector<bool> taken(26, false);
      for (char &ch : s) {
        if (!taken[ch-'a'])
          ++xc[ch - 'a'], taken[ch - 'a'] = true;
        ++fxc[ch - 'a'];
      }
    }
    for (int al = 0; al < 26; ++al) {
      if (xc[al] > 1) {
        ans += (log10(xc[al]) * (rot == 1? -1 : 1));
      }
      if (fxc[al] > 1) {
        ans += (log10(fxc[al]) * k * (rot == 1? 1 : -1));
      }
    }
  }
}

int v[N];
bool check (string &s) {
  int sz = (int)s.size();
  for (int i = 0; i < sz; ++i) {
    v[i] = (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u');
  }

  int consonent, vowel;

  for (int len = 2; len <= 3; ++len) {
    for (int i = 0; i + len - 1 <= sz - 1; ++i) {
      consonent = vowel = 0;
      for (int j = i; j <= i + len - 1; ++j)  {
        consonent += (v[j] == 0), vowel += (v[j] == 1);
      }
      if (vowel < consonent) return false;
    }
  }
  return true;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie (nullptr);
  cout.precision(7);
  cout << fixed;
  int tc;
  cin >> tc;

  while (tc--) {
    S[0].clear(), S[1].clear();
    int l;
    cin >> l;
    string s;

    for (int i = 0; i < l; ++i) {
      cin >> s;
      if (check(s)) S[0].push_back(s);
      else S[1].push_back(s);
    }

    ans = 0.0;
    calc();

    if (ans >= 7) cout << "Infinity\n";
    else cout << pow(10, ans) << '\n';
  }

  return 0;
}
