#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

// Tricky to find state for dp, we can work with prefixes, the key observation
// is that any valid permutation (which satisfies the inequality) simply
// signifies relative ordering between the elements, so while inserting new
// larger elements some shift operations can be done to keep the order between
// consecutive elements as required, so working on prefixes what we just need
// to know about the permutation is that what all elements made it up and where
// did it end.
// Let's define dp[i][j] := No. of valid permutations using elements [1...i]
// such that the permutation ends at j
// Now we need to guess k (elements just before j) so that we can calc from dp[i-1][k]
//
// if s[i] == '>':
// if (k < j) no such permutation from dp[i-1][k] will help in building dp[i][j]
// if (k >= j) let us add all the numbers greater than or equal to k in the
// // permutation from dp[i-1][k] by 1, so now we can safely add j at last
//
// else if s[i] == '<':
// if (k < j) let us add all the number greath than or equal to k in the
// // permutation from dp[i-1][k] by 1, so now we can safely add j at last
// if (k >= j) no such permutation from dp[i-1][k] will help in building dp[i][j]
//
// Hence, if (s[i] == '>'): dp[i][j] = pref[i-1] - pref[j-1]
// else dp[i][j] = pref[j-1]
// where pref[j] = pref[j-1] + dp[i-1][j]
// base case dp[1][j] = 1

const int MOD = (int)1e9 + 7;
const int N = 3004;
string s;
int n;
int dp[N][N];
int pref[N];

inline int add (int a, int b) {
   return (a + b)%MOD;
}

void solve()
{
   // or dp[1][1] = 1;
   s = "##" + s; // for better indexing
   for (int i = 1; i <= n; ++i)
      dp[1][i] = 1;

   for (int i = 2; i <= n; ++i) {
      pref[0] = 0;
      for (int j = 1; j <= n; ++j)
         pref[j] = add(pref[j-1], dp[i-1][j]);

      for (int j = 1; j <= n; ++j) {
         dp[i][j] = 0;
         if (s[i] == '>')
            dp[i][j] = (pref[i-1] - pref[j-1] + MOD) % MOD;
         else
            dp[i][j] = pref[j-1];
      }
   }
   int total = 0;
   for (int i = 1; i <= n; ++i)
      total = add(total, dp[n][i]);
   cout << total << '\n';
}

signed main()
{
   IOS; PREC;
   cin >> n;
   cin >> s;
   assert(n - 1 == (int)s.size());
   solve();

   return EXIT_SUCCESS;
}
