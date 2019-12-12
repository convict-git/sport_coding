#include <bits/stdc++.h>
using namespace std;
#pragma GCC       optimize ("Ofast")
#pragma GCC       optimize ("unroll-loops")
#pragma GCC       target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

const int MAX_P = 150000;
const int N = (int)1e6 + 10;
vector <int> primes = {2}, powers;
vector<pair<int,int>> prime_divisor[N+1];
int factor_num[N], factor_den[N];
int v[N];
vector <string> A, B;
vector <int> taken_care;
vector<int> xcA(26), xcB(26);
vector<int> fxcA(26), fxcB(26);
int k;

void sieve() {
  vector <bool> isPrime(MAX_P + 1, true);
  for (int i = 3; i*2 <= MAX_P; i += 2) {
    int p = 0;
    while (1ll * i*(i + p) <= MAX_P) isPrime[i*(i + p)] = false, ++p;
  }
  for (int i = 3; i <= MAX_P; i += 2) {
    if (isPrime[i]) primes.push_back(i);
  }

  for (int i = 2; i <= N; ++i) {
    int i_ref = i;
    for (int p : primes) {
      if (1ll*p*p > 1ll*i_ref) break;
      int alp = 0;
      while (i_ref % p == 0) i_ref /= p, alp++;
      if (alp) prime_divisor[i].push_back(make_pair(p, alp));
    }
    if (i_ref != 1) {
      prime_divisor[i].push_back(make_pair(i_ref, 1));
    }
  }
}

void calcA () {
  xcA.assign(26, 0);
  fxcA.assign(26, 0);
  k = (int)A.size();

  for (string& s : A) {
    vector<bool> taken(26, false);
    for (char &ch : s) {
      if (!taken[ch-'a'])
        ++xcA[ch - 'a'], taken[ch - 'a'] = true;
      ++fxcA[ch - 'a'];
    }
  }
  for (int al = 0; al < 26; ++al) {
    if (xcA[al] > 1) {
      for (pair<int,int> pr : prime_divisor[xcA[al]]) {
        int p = pr.first;
        taken_care.push_back(p);
      }
    }
    if (fxcA[al] > 1) {
      for (pair<int,int> pr : prime_divisor[fxcA[al]]) {
        int p = pr.first;
        taken_care.push_back(p);
      }
    }
  }
}

void calcB () {
  xcB.assign(26, 0);
  fxcB.assign(26, 0);

  k = (int)B.size();
  for (string& s : B) {
    vector<bool> taken(26, false);
    for (char &ch : s) {
      if (!taken[ch-'a'])
        ++xcB[ch - 'a'], taken[ch - 'a'] = true;
      ++fxcB[ch - 'a'];
    }
  }
  for (int al = 0; al < 26; ++al) {
    if (xcB[al] > 1) {
      for (pair<int,int> pr : prime_divisor[xcB[al]]) {
        int p = pr.first;
        taken_care.push_back(p);
      }
    }
    if (fxcB[al] > 1) {
      for (pair<int,int> pr : prime_divisor[fxcB[al]]) {
        int p = pr.first;
        taken_care.push_back(p);
      }
    }
  }
}

void calccA() {
  k = (int)A.size();
  for (int al = 0; al < 26; ++al) {
    if (xcA[al] > 1) {
      for (pair<int,int> pr : prime_divisor[xcA[al]]) {
        int p = pr.first, alp = pr.second;
        factor_num[p] += alp;
      }
    }
    if (fxcA[al] > 1) {
      for (pair<int,int> pr : prime_divisor[fxcA[al]]) {
        int p = pr.first, alp = pr.second;
        factor_num[p] -=  k * alp;
      }
    }
  }
}


void calccB() {
  k = (int)B.size();
  for (int al = 0; al < 26; ++al) {
    if (xcB[al] > 1) {
      for (pair<int,int> pr : prime_divisor[xcB[al]]) {
        int p = pr.first, alp = pr.second;
        factor_den[p] += alp;
      }
    }
    if (fxcB[al] > 1) {
      for (pair<int,int> pr : prime_divisor[fxcB[al]]) {
        int p = pr.first, alp = pr.second;
        factor_den[p] -=  k * alp;
      }
    }
  }
}

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
  sieve();
  int tc;
  cin >> tc;

  while (tc--) {
    taken_care.clear();
    A.clear(), B.clear();
    int l;
    cin >> l;
    string s;

    for (int i = 0; i < l; ++i) {
      cin >> s;
      if (check(s)) A.push_back(s);
      else B.push_back(s);
    }

    calcA();
    calcB();

    sort(taken_care.begin(), taken_care.end());
    taken_care.erase(unique(taken_care.begin(), taken_care.end()), taken_care.end());

    for (int p : taken_care) factor_num[p] = factor_den[p] = 0;
    calccA();
    calccB();

    long double ans = 0;
    for (int p : taken_care) {
      int alp = factor_num[p] - factor_den[p];
      // if (alp) ans *= (long double) pow (p, alp);
      ans += log10(p) * alp;
    }
    if (ans >= 7) cout << "Infinity\n";
    else cout << pow(10, ans) << '\n';
  }

  return 0;
}
