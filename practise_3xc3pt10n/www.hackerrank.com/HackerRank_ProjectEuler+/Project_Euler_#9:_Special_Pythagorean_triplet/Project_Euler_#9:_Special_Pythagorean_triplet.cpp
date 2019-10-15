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
int solve(int n) {
   int mx_val = -1;
   for (int a = 0; a < n; ++a) {
      int num_b = n*n - 2*n*a, den_b = 2*(n - a);
      int b = num_b/den_b, c = n - a - b;
      if (num_b%den_b == 0 && b > a && c > b) {
         mx_val = max(a*b*c, mx_val);
      }
   }
   return mx_val;
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) {
      int n;
      cin >> n;
      cout << solve(n) << '\n';
   }
   return EXIT_SUCCESS;
}

