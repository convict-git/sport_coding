#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ] "
#define x        first
#define y        second
// using ll = long long;

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

const int N = (int)1e6 + 10;
vector <int> ar;
int L[N], U[N];
int n, szl, szu;

void solve() {
   reverse(ar.begin(), ar.end()); // because we want to start from i so reversing means ending at i

   szl = szu = 0;
   int mx_sz = 0;
   for (int i = 0; i < n; ++i) {
      int ll = 0, hl = szl - 1;
      while (ll <= hl) { // LIS
         int g = (ll + hl)/2;
         if (ar[i] > L[g]) ll = g + 1;
         else hl = g - 1;
      }
      if (ll == szl) ++szl;
      L[ll] = ar[i];

      int lu = 0, hu = szu - 1;
      while (lu <= hu) { // LDS
         int g = (lu + hu)/2;
         if (ar[i] < U[g]) lu = g + 1;
         else hu = g - 1;
      }
      if (lu == szu) ++szu;
      U[lu] = ar[i];

      int LIS = ll + 1, LDS = lu + 1;

      mx_sz = max(mx_sz, LIS + LDS -1);
   }
   cout << mx_sz << '\n';
}

void read() {
   cin >> n;
   ar.assign(n, 0);
   for (int i = 0; i < n; ++i) cin >> ar[i];
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) read(), solve();

   return EXIT_SUCCESS;
}

