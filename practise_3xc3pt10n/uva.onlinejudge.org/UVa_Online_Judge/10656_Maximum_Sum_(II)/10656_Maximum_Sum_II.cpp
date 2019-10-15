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

signed main() {
   IOS; PREC;
   int n;
   vector <int> Arr;

   while (cin >> n, n) {
      Arr.assign(n, 0);
      int ctr = 0;
      for (int i = 0; i < n; ++i) {
         cin >> Arr[i];
         assert(Arr[i] >= 0);
         if (Arr[i] > 0) cout << (ctr ? " " : "") << Arr[i], ++ctr;
      }
      if (ctr == 0) cout << 0;
      cout << '\n';
   }


   return EXIT_SUCCESS;
}

