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

ll n;
vector <ll> even_values;

void pre_calc() {
   even_values.push_back(2);
   for (ll i = 1, j = 2; i + j <= (ll)4e16;) {
      ll tmp = i + j;
      if (tmp % 2 == 0) even_values.push_back(tmp);
      i = j;
      j = tmp;
   }
}

signed main() {
   IOS; PREC;
   pre_calc();
   int tc; cin >> tc;
   while (tc--) {
      cin >> n;
      ll ans = 0;
      for (ll val : even_values) {
         if (val <= n) ans += val;
      }
      cout << ans << '\n';
   }

   return EXIT_SUCCESS;
}

