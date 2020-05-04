#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    "[ " << #x << " : " << x << " ]"
#define x        first
#define y        second
using namespace std;
using ll = long long;

const ll Mod = (ll)2e9 + 11;

int mul(const ll &a, const ll &b) {
   return (int) ((a * b) % Mod);
}

int solve(int n) {
   if (n <= 2) return 1;
   int pw = n - 2;
   int ans = 1;
   while (pw) {
      if (pw & 1)
         ans = mul(1ll * ans, 1ll * n);
      n = mul(1ll * n, 1ll * n);
      pw >>= 1;
   }
   return ans;
}

signed main() {
   int tc, n;
   cin >> tc;
   for (int i = 1; i <= tc; ++i) {
      cin >> n;
      cout << "Case #" << i << ": " << solve(n) << '\n';
   }
   return EXIT_SUCCESS;
}

