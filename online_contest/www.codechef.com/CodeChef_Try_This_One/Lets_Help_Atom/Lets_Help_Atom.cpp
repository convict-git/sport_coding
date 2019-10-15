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

int q;
int cur_idx;
vector <string> stck;

signed main() {
   IOS; PREC;
   stck.push_back("");
   cin >> q;
   while (q--) {
      int type, k;
      string apnd;
      cin >> type;
      if (type == 1) {
         cin >> apnd;
         stck.push_back(stck[stck.size() - 1] + apnd);
      }
      else if (type == 2) {
         cin >> k;
         string tmp = stck[stck.size() - 1];
         int sz = (int)tmp.size();
         tmp.resize(sz - k);
         stck.push_back(tmp);

      }
      else if (type == 3) {
         cin >> k;
         cout << stck[stck.size() - 1][k - 1] << '\n';
      }
      else if (type == 4) {
         stck.pop_back();
      }
      else assert(false);
   }

   return EXIT_SUCCESS;
}

