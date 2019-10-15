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

const int M = (int)1e6 + 10;
const int N = 21;

long long dp[N][M];
int Par[N][M];
int S[N];
int total_len, n;

void solve() {
   for (int s = 0; s <= total_len; ++s) {
      for (int i = 0; i <= n; ++i) {
         if (!s || !i) dp[i][s] = 0, Par[i][s] = -1;
         else if (S[i] <= s) {
            if (dp[i - 1][s] > dp[i - 1][s - S[i]] + 1ll * S[i]) {
               dp[i][s] = dp[i - 1][s];
               Par[i][s] = i - 1;
            }
            else {
               dp[i][s] = dp[i - 1][s - S[i]] + 1ll * S[i];
               Par[i][s] = i;
            }
         }
         else {
            dp[i][s] = dp[i - 1][s];
            Par[i][s] = i - 1;
         }
      }
   }

   long long sum = dp[n][total_len];
   vector <int> ans;
   int i = n, s = total_len;
   while (Par[i][s] != -1) {
      if (Par[i][s] == i) {
         ans.push_back(i);
         s -= S[i];
         --i;
      }
      else {
         i = Par[i][s];
      }
   }
   reverse(ans.begin(), ans.end());
   for (int i = 0; i < (int)ans.size(); ++i) {
      cout << S[ans[i]] << ' ';
   }
   cout << "sum:" << sum << '\n';
}

void read() {
   cin >> n;
   for (int i = 0; i < n; ++i) cin >> S[i + 1];
}

signed main() {
   IOS; PREC;
   while (cin >> total_len) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

