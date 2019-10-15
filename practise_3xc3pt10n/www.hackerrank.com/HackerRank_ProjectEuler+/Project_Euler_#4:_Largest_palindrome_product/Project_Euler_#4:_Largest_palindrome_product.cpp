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

const int N = (int)1e3;
vector <int> palindromes;

bool isPalindrome(int p) {
   string dig, rev_dig;
   rev_dig = dig = to_string(p);
   reverse(rev_dig.begin(), rev_dig.end());
   return rev_dig == dig;

//    vector <int> digit;
//    while (p) {
//       dig.push_back(char('0'+p%10));
//       // digit.push_back(p%10);
//       p /= 10;
//    }
//    int sz = (int)digit.size();
//    for (int i = 0; i < sz; ++i) {
//       if (digit[i] != digit[sz - i - 1])
//          return false;
//    }
//    return true;
}

void precalc() {
   for (int i = 100; i < 1000; ++i) {
      for (int j = i; j < 1000; ++j) {
         if (isPalindrome(i * j)) palindromes.push_back(i * j);
      }
   }
   sort(palindromes.begin(), palindromes.end());
}

int solve(int n) {
   int sz = (int)palindromes.size();
   int l = 0, h = sz - 1;
   while (l <= h) {
      int g = (l + h)/2;
      if (palindromes[g] < n) l = g + 1;
      else h = g - 1;
   }
   return palindromes[h];
}

signed main() {
   IOS; PREC;
   precalc();
   int tc; cin >> tc;
   while (tc--) {
      int n;
      cin >> n;
      cout << solve(n) << '\n';
   }

   return EXIT_SUCCESS;
}

