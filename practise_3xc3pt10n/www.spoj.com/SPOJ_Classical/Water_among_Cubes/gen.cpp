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

template <class T = int> T giveRand (const T& low, const T& high) {
   auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
   mt19937 mt_rand(seed);
   return uniform_int_distribution<T> (low, high)(mt_rand); //closed interval [low, high]
}

signed main() {
   IOS; PREC;
   int tc = 100;
   cout << tc << "\n";
   while (tc--) {
      int n = giveRand(1, 100);
      int m = giveRand(1, 100);
      cout << n << ' ' << m << '\n';
      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < m; ++j) {
            cout << giveRand(1, 10000) << ' ';
         }
         cout << '\n';
      }
   }
   return EXIT_SUCCESS;
}


