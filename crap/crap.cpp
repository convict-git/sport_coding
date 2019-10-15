#include <bits/stdc++.h>
using namespace std;

const int N = (int)2e6 + 10;
int cnt[N], dp[N], ar[N];
int n, cur;
long long ans = 0;

// cnt[i] : number of prefixes which have xor i
// dp[i] : sum of j (ending) of all prefixes which have xor i
//

int main() {
   int tc;
   cin >> tc;
   while (tc--) {
      for (int i = 0; i < N; ++i)
         cnt[i] = dp[i] = 0;

      ans = 0, cur = 0;

      cin >> n;
      for (int i = 0; i < n; ++i) {
         cin >> ar[i];
         cur ^= ar[i];
         if (cnt[cur]) {
            ans += 1ll * (i - 2) * cnt[cur] - dp[cur];
         }
         ++cnt[cur], dp[cur] += i;
      }
      cout << ans << '\n';
   }

   return 0;
}
