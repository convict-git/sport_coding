#include         <bits/stdc++.h>
using namespace std;
#ifndef CONVICTION
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ] "
#define x        first
#define y        second
using ll = long long;
using ff = long double;
using pii = pair<int,int>;

#define debug(args...) { \
   /* WARNING : do NOT compile this debug func calls with following flags: // \
    * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
   cerr << fixed << setprecision(15) << " [ " <<  *it << " : " << a  << " ] "<< ' ';
   err(++it, args...);
}

// DP on digits, find number of integers [1...k] such that there sum is divisible by d
// let dp(pos, rem_sum, les) := if les is true, no. of ways of getting 'rem_sum' as
// remainder of the sum of digits used (from max significant) such that digit
// from [1..pos] never exceeded the k's subpart
// else if les is false, digits chosen are such that it is equal to the k's subpart
// from [1..pos] and remainder of the sum of digits used is 'rem_sum'
//
// at pos, when les is false, cur digit used must be equal to corresponding digit in k,
// and dp should be calc from pos-1 when les was false
// and
// at pos, when les is true, cur digit can be anything [0...9], and dp should be calc
// from pos-1 from both les was false (for digits [0....k[pos]-1]) or as well as true
// (for digits [0....9]).

const int N = (int)1e4 + 10, S = 104;
const int MOD = (int)1e9 + 7;

int dp[N][S][2];
int n, d;
string s;

inline int add (int a, int b) {
   return (a + b)%MOD;
}

void solve() {
   n = (int)s.size();
   s = ' ' + s;

   for (int dg = 0; dg < s[1] - '0'; ++dg)
      dp[1][dg % d][true] += 1;

   dp[1][(s[1] - '0')%d][false] += 1;

   // or equivalent base case : dp[0][0][0] = 1 // and start dp from pos = 1

   for (int pos = 2; pos <= n; ++pos) {
      for (int rem = 0; rem < d; ++rem) {
         for (bool les : {false, true}) {
            int mx_digit = 9;
            if (!les)
            {
               mx_digit = s[pos] - '0';
            }
            for (int dg = 0; dg <= mx_digit; ++dg) {
               bool is_les = (les || (dg < s[pos] - '0'));
               dp[pos][(rem + dg) % d][is_les] =
                  add(dp[pos][(rem + dg) % d][is_les], dp[pos - 1][rem][les]);
            }
         }
      }
   }
   cout << (dp[n][0][0] + dp[n][0][1] - 1 + MOD) % MOD << '\n';
   // ans - 1 because 000000..000 was allowed
}

signed main() {
   IOS; PREC;
   cin >> s >> d;
   solve();

   return EXIT_SUCCESS;
}
