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

const int N = 16;
int val[N][N];
int n;

int solve() {
   cin >> n;
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= i; ++j) {
         cin >> val[i][j];
      }
   }
   for (int i = n - 2; i >= 0; --i) {
      for (int j = 0; j <= i; ++j) {
         val[i][j] += max(val[i + 1][j], val[i + 1][j + 1]);
      }
   }
   return val[0][0];
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) cout << solve() << "\n";

   return EXIT_SUCCESS;
}

