#include         <bits/stdc++.h>
using namespace std;
#ifndef CONVICTION
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ] "
#define x        first
#define y        second
using ll = long long;
using ff = long double;
using pii = pair<int,int>;

#define debug(args...) \
{ \
/* WARNING : do NOT compile this debug func calls with following flags: // \
 * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); \
   istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it)
{
   it->empty(); cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
	cerr << fixed << setprecision(15)
      << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

signed main()
{
   IOS; PREC;

   int n = 50000, k = 500;
   cout << n << ' ' << k << '\n';
   int x = 1, cnt = 2;
   for (int i = 0; i < n - 1;) {
      if (i < n - 1) cout << cnt << ' ' << x << '\n', ++i, ++cnt;
      if (i < n - 1) cout << cnt << ' ' << x << '\n', ++i, ++cnt;
      x = cnt - 2;
   }
   return EXIT_SUCCESS;
}

