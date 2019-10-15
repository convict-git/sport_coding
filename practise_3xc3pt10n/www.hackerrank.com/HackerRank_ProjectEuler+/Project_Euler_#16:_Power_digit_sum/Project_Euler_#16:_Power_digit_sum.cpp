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

int solve(int n) {
   vector <int> digit = {1};
   for (int i = 0; i < n; ++i) {
      int carry = 0;
      for (int j = 0; j < (int)digit.size(); ++j) {
         int cur = digit[j]*2 + carry;
         digit[j] = cur % 10;
         cur /= 10;
         carry = cur;
      }
      while (carry) {
         digit.push_back(carry%10);
         carry /= 10;
      }
   }
   int sum = 0;
   for (int i = 0; i < (int)digit.size(); ++i)
      sum += digit[i];
   return sum;
}

signed main() {
   IOS; PREC;

   int tc; cin >> tc;
   while (tc--)  {
      int n; cin >> n;
      cout << solve(n) << '\n';
   }

   return EXIT_SUCCESS;
}

