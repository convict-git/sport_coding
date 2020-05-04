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

int s, d;

void solve() {
   int mx_val = INT_MIN;
   for (int sub_set = 0; sub_set < (1 << 12); ++sub_set) {
      bool change = false;
      int total_val = 0;

      for (int i = 0; i < 12; ++i)
         total_val += (sub_set & (1 << i) ? s : -1 * d);

      for (int i = 0; i < 8 && !change; ++i) {
         int val = 0;
         for (int j = 0; j < 5; ++j) {
            val += (sub_set & (1 << (i + j)) ? s : -1 * d);
         }
         if (val > 0) change = true;
      }
      if (!change) mx_val = max(mx_val, total_val);
   }
   if (mx_val >= 0) cout << mx_val << '\n';
   else cout << "Deficit\n";
}

signed main() {
   IOS; PREC;
   while (cin >> s >> d) {
      solve();
   }

   return EXIT_SUCCESS;
}

