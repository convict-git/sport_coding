#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (4); cout << fixed
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
using ld = long double;
int p, q, r, s, t, u;
ld eps = 1e-9;

ld fn(ld n) {
   return p*exp(-n) + q*sin(n) + r*cos(n) + s*tan(n) + t*n*n;
}

void bisection_method() {
   ld low = 0, hi = 1, g = (low + hi)/2;
   int counter = 100;
   while (counter--) {
      g = (low + hi)/2;
      if (fn(g) + u > 0) low = g + eps;
      else hi = g - eps;
   }
   if (fabs(u + fn(g)) > eps)
      cout << "No solution\n";
   else cout << fabs(g) << '\n';
}

signed main() {
   IOS; PREC;
   while (cin >> p >> q >> r >> s >> t >> u) {
      bisection_method();
   }

   return EXIT_SUCCESS;
}

