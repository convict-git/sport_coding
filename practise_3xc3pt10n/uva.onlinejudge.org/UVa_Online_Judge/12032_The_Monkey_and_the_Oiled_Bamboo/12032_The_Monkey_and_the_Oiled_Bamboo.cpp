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

const int N = (int)1e5 + 10;
int n, rung[N];

void solve(int tc) {
   int l = 1, h = (int)1e7, k, g;
   while (l <= h) {
      g = k = (l + h)/2;

      int i, cur = 0;
      for (i = 0, cur = 0; i < n && k > 0;) {
         if (rung[i] - cur < k)
            cur = rung[i], ++i;
         else if (rung[i] - cur == k)
            cur = rung[i], --k, ++i;
         else {
            break;
         }
      }
      if (i == n) h = g - 1;
      else l = g + 1;
   }
   cout << "Case " << tc << ": " << l << '\n';
}
void read() {
   cin >> n;
   for (int i = 0; i < n; ++i) cin >> rung[i];
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   for (int i = 1; i <= tc; ++i) read(), solve(i);

   return EXIT_SUCCESS;
}

