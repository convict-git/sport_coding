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
   cerr << " (Line : " << __LINE__ << ") " << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

signed main() {
   IOS; PREC;
   int n;
   cin >> n;
   vector <int> ar(n);
   for (int i = 0; i < n; ++i) cin >> ar[i];

   bool ok = true;
   while (ok) {
      ok = false;
      for (int i = 0; i < n - 2; ++i) {
         if (ar[i] > ar[i + 2]) swap(ar[i], ar[i + 2]), ok = true;
      }
   }

   ok = true;
   int idx = -1;
   for (int i = 0; i < n - 1; ++i) {
      if (ar[i] > ar[i + 1]) {
         idx = i;
         ok = false;
         break;
      }
   }
   if (ok) cout << "OK\n";
   else cout << idx << "\n";
   return EXIT_SUCCESS;
}

