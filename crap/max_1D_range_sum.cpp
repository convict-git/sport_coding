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
const int N = (int)1e6 + 10;
int dp[N][2], Par[N][2], Ar[N];
int n;

int max_1D_range_sum() {
   for (int i = 0; i < n; ++i) Par[i][0] = Par[i][1] = -1;

   dp[0][0] = Ar[0], dp[0][1] = INT_MIN;

   for (int i = 1; i < n; ++i) {
      if (Ar[i] + dp[i - 1][0] > Ar[i]) { // consider past
         dp[i][0] = Ar[i] + dp[i - 1][0];
         Par[i][0] = i - 1;
      }
      else {
         dp[i][0] = Ar[i];
         Par[i][0] = -1;
      }
      if (dp[i - 1][0] > dp[i - 1][1]) {
         dp[i][1] = dp[i - 1][0];
         Par[i][1] = i - 1;
      }
      else {
         dp[i][1] = dp[i - 1][1];
         Par[i][1] = Par[i - 1][1];
      }
   }
   return max(dp[n - 1][0], dp[n - 1][1]);
}

// this is temporary... you are beautiful :*
vector <int> back_track(int idx) {
   vector <int> solution;
   assert(idx >= 0 && idx < n);

   bool up = dp[idx][0] > dp[idx][1];
   if (!up) idx = Par[idx][1];

   while (idx != -1) {
      solution.push_back(idx);
      idx = Par[idx][0];
   }
   reverse(solution.begin(), solution.end());
   return solution;
}

signed main() {
   IOS; PREC;
   cin >> n;
   for (int i = 0; i < n; ++i) {
      cin >> Ar[i];
   }
   int mx = max_1D_range_sum();
   cout << "mx " << mx << '\n';
   vector <int> solution = back_track(n - 1);
   for (int v : solution) cout << "[" << v << ',' << Ar[v] << "]" << ' ';
   cout << '\n';
   return EXIT_SUCCESS;
}


