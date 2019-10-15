/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr)
#define PREC                                                                   \
  cout.precision(10);                                                          \
  cout << fixed
#define bg(x) " [ " << #x << " : " << (x) << " ]"
#define x first
#define y second

#define debug(args...)                                                         \
  {                                                                            \
    string _s = #args;                                                         \
    replace(_s.begin(), _s.end(), ',', ' ');                                   \
    stringstream _ss(_s);                                                      \
    istream_iterator<string> _it(_ss);                                         \
    err(_it, args);                                                            \
  }
void err(istream_iterator<string> it) {
  it->empty();
  cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
  cerr << " [ " << *it << " : " << a << " ] " << ' ';
  err(++it, args...);
}
using ll = long long;

const int MAX_P = 300;
vector<int> primes = {2};
void sieve() {
  vector<bool> isPrime(MAX_P + 1, true);
  for (int i = 3; i * 2 <= MAX_P; i += 2) {
    int p = 0;
    while (1ll * i * (i + p) <= MAX_P)
      isPrime[i * (i + p)] = false, ++p;
  }
  for (int i = 3; i <= MAX_P; i += 2) {
    if (isPrime[i])
      primes.push_back(i);
  }
}

int total_div(int n) {
  int td = 1;
  int n_ref = n;
  for (int p : primes) {
    if (1ll * p * p > n_ref)
      break;
    int alpha = 0;
    while (n % p == 0)
      n /= p, ++alpha;
    td *= (1 + alpha);
  }
  td *= (1 + (n != 1));
  return td;
}

ll solve(int n) {
  for (int i = 1; i <= 41040; ++i) {
    ll tri = (1ll * i * (i + 1)) / 2;
    ll ansl = total_div((i & 1 ? i : i / 2));
    ll ansr = total_div(((i + 1) & 1 ? i + 1 : (i + 1) / 2));
    ll ans = ansl * ansr;
    if (ans > n)
      return tri;
  }
  assert(false);
  return -1;
}

signed main() {
  IOS;
  PREC;
  sieve();
  int tc;
  cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    cout << solve(n) << '\n';
  }
  return EXIT_SUCCESS;
}
