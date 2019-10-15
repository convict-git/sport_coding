#include <bits/stdc++.h>
using namespace std;
const int Mod = (int)1e9 + 7;

// gives 1 + a^1 + a^2 + .... + a^k-1 in log(k)
int sum_gp (int a, int k) {
   int a_sq = int(1ll * a * a % Mod);
   if (k == 1) return 1;
   else if (k & 1) return int((1 + 1ll * a * sum_gp(a, k - 1)) % Mod);
   else return int(1ll * (1 + a) * sum_gp (a_sq, k/2) % Mod);
}
