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

int heads, knights;
vector <int> diameter, heights;

signed main() {
   IOS; PREC;
   while (cin >> heads >> knights, heads || knights) {
      diameter.assign(heads, 0);
      heights.assign(knights, 0);
      for (int i = 0; i < heads; ++i) cin >> diameter[i];
      for (int i = 0; i < knights; ++i) cin >> heights[i];
      sort(diameter.begin(), diameter.end());
      sort(heights.begin(), heights.end());

      bool ok = true;
      int ans = 0;
      for (int i = 0, cur_idx = 0; i < heads && ok; ++i) {
         int l = cur_idx, h = knights - 1;
         while (l <= h) {
            int g = (l + h)/2;
            if (heights[g] >= diameter[i]) h = g - 1;
            else l = g + 1;
         }
         if (l == knights) ok = false;
         else ans += heights[l];
         cur_idx = l + 1;
      }
      if (ok) cout << ans << '\n';
      else cout << "Loowater is doomed!\n";
   }
   return EXIT_SUCCESS;
}

