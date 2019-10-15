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
   string st  = "", tmp;
   while (cin >> tmp) st += tmp;

   int row, col;
   row = floor(sqrt((int)st.size()));
   col = ceil(sqrt((int)st.size()));

   for (int i = 0; i < col; ++i) {
      for (int j = 0; j < row; ++j) {
         if (col*j + i < (int)st.size()) {
            cout << st[col*j + i];
         }
      }
      cout << ' ';
   }
   cout << '\n';
   return EXIT_SUCCESS;
}

