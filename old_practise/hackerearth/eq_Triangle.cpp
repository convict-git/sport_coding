#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
int n;

void solve() {
   int ans = 0;
   for (int i = 1; i < n; ++i) {
      ans += ((n - i)/2) * ((i + 1) * i)/2;
   }
   cout << ans << '\n';
}

signed main() {
   cin >> n;
   solve();

	return EXIT_SUCCESS;
}

