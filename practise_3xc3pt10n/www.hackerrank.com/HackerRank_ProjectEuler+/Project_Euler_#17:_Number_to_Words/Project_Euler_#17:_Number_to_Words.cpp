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

vector <string> digit = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
vector <string> names = {"", "Thousand", "Million", "Billion", "Trillion"};
vector <string> tens = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
vector <string> ties = {"Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

string input;
inline string add(const string &s1, const string &s2) {
   if (s1.size() && s2.size()) {
      return s1 + " " + s2;
   }
   else return s1 + s2;
}

// takes input in segments of three
string solve(int idx, int level) { // level for thous, million, billion to be appended in the end
   if (idx >= (int)input.size()) return "";
   string cur = "";
   int od, td, hd;
   od = int(input[idx] - '0'), td = int(input[idx + 1] - '0'), hd = int(input[idx + 2] - '0');
   if (hd) cur = add(cur, add(digit[hd], "Hundred"));
   if (td) {
      if (td == 1) {
         cur = add(cur, tens[od]);
      } else {
         cur = add(cur, ties[td - 1]);
         if (od) cur = add(cur, digit[od]);
      }
   }
   else {
      if (od) cur = add(cur, digit[od]);
   }
   if (cur != "") cur = add(cur, names[level]);
   return add(solve(idx + 3, level + 1), cur);
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) {
      cin >> input;
      while ((int)input.size() % 3 != 0) input = "0" + input;
      reverse(input.begin(), input.end());
      // debug(input);
      if (input == "000") cout << "Zero\n";
      else cout << solve(0, 0) << "\n";
   }

   return EXIT_SUCCESS;
}

