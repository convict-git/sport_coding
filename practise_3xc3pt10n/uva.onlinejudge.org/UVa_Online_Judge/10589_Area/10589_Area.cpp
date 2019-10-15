#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (5); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ]"
#define x        first
#define y        second
using ll = long long;

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
const long double eps = 1e-7;
using ld = long double;

int X[] = {0, 1, 1, 0};
int Y[] = {0, 0, 1, 1};
int a;
int n, m;

inline bool is_inside(ld xx, ld yy) {
   for (int i = 0; i < 4; ++i) {
      if ((xx - X[i]*a)*(xx - X[i]*a) + (yy - Y[i]*a)*(yy - Y[i]*a) <= a*a) continue;
      return false;
   }
   return true;
}

void read() {
   cin >> a;
   m = 0;
   for (int i = 0; i < n; ++i) {
      ld xx, yy;
      cin >> xx >> yy;
      if (is_inside(xx, yy)) ++m;
   }
   cout << (m*(long double)(a*a))/(long double)n << '\n';
}

signed main() {
   IOS; PREC;
   while (cin >> n, n) {
      read();
   }

   return EXIT_SUCCESS;
}

