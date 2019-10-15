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

int gcd(int a, int b) {
   if (b > a) swap(a, b);
   if (b == 0) return a;
   else return gcd(b, a%b);
}

int solve(int n) {
   int ans = 1;
   for (int i = 2; i <= n; ++i) {
      ans = (ans * i)/gcd(ans, i);
   }
   return ans;
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) {
      int n; cin >> n;
      cout << solve(n) << '\n';
   }

   return EXIT_SUCCESS;
}

