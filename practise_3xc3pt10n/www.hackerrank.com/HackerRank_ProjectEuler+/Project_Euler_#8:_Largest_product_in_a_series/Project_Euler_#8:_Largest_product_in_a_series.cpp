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

int solve(string n, int k) {
   int sz = (int)n.size();
   int mx_prod = 0;
   for (int i = 0; i <= sz - k; ++i) {
      int prod = 1;
      for (int j = 0; j < k; ++j) {
         prod *= int(n[i + j] - '0');
      }
      mx_prod = max(mx_prod, prod);
   }
   return mx_prod;
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) {
      int k, n; string nst;
      cin >> n >> k;
      cin >> nst;
      cout << solve(nst, k) << '\n';
   }

   return EXIT_SUCCESS;
}

