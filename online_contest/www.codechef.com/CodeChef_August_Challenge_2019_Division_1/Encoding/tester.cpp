#include      <bits/stdc++.h>
using namespace std;

const int PRIME = (int)1e9 + 7;
const int N = (int)1e5 + 10;

int add (int x, int y) {
   return (x + y) % PRIME;
}
int mul (int x, int y) {
   return int((1ll * x * y) % PRIME);
}
int sub (int x, int y) {
   return (x - y + PRIME) % PRIME;
}
vector <int> pw;
void pre_calc(int m) {
   while ((int)pw.size() <= m) {
      pw.push_back(mul(pw.back(), 10));
   }
}

int cal_one(long long m) {
   string s = "";
   if (m == 0) s = "0";
   while (m) {
      s += char((m % 10) + '0');
      m /= 10;
   }
   reverse(s.begin(), s.end());
   int n = (int)s.size();
   int ans = mul(pw[n - 1], s[0] - '0');
   for (int i = 1; i < n; ++i) {
      if (s[i] != s[i - 1]) {
         ans = add(ans, mul(pw[n - i - 1], s[i] - '0'));
      }
   }
   return ans;
}

int main() {
   pw.push_back(1);
   int tc;
   cin >> tc;
   while (tc--) {
      int l, r;
      long long L, R;
      cin >> l >> L;
      cin >> r >> R;
      int ans = 0;
      pre_calc(max(l, r));
      for (long long i = L; i <= R; ++i) {
         ans = add(ans, cal_one(i));
      }
      cout << ans << '\n';
   }

   return 0;
}


