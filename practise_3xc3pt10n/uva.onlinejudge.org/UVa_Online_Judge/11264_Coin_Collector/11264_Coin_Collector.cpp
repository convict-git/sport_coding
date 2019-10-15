#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ]"
#define x        first
#define y        second

#define debug(args...) { \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}
using ll = long long;
const int N = 1005;
vector <ll> coins;
vector <bool> taken;
int n;

int withdraw(ll m) {
   if (m <= 0) return 0;
   int l = 0, h = n - 1;
   while (l <= h) {
      int g = (l + h)/2;
      if (coins[g] <= m) l = g + 1;
      else h = g - 1;
   }

   if (!(h >= 0 && h < n)) {
      debug(l, h, m, coins[0]);
      assert(false);
   }

   if (taken[h]) return withdraw(m - coins[h]);
   else {
      taken[h] = true;
      return withdraw(m - coins[h]) + 1;
   }
}
void read() {
   cin >> n;
   coins.assign(n, 0);
   for (int i = 0; i < n; ++i) cin >> coins[i];
}
void solve() {
   ll sum = 0;
   taken.assign(n, false);
   for (int i = 0; i < n - 1; ++i) {
      if (sum + coins[i] < coins[i + 1])
         sum += coins[i];
   }
   cout << withdraw(sum) + 1 << '\n';
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) {
      read();
      solve();
   }
   return EXIT_SUCCESS;
}

