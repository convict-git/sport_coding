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

const int N = (int)2e5 + 10;
ll seg[4 * N];
ll dp[N];
int h[N], v[N];
int n;

void modify(int l, int r, int idx, int x, ll val) {
   if (l > idx || r < idx) return;
   if (l == r) {
      seg[x] = max(seg[x], val);
      return;
   }
   int mid = (l+r)/2;
   modify(l, mid, idx, x + x + 1, val);
   modify(mid + 1, r, idx, x + x + 2, val);
   seg[x] = max(seg[x + x + 1], seg[x + x + 2]);
}

ll query(int l, int r, int ql, int qr, int x) {
   if (r < ql || l > qr) return LLONG_MIN;
   if (l >= ql && r <= qr) return seg[x];
   int mid = (l+r)/2;
   ll left = query(l, mid, ql, qr, x + x + 1);
   ll right = query(mid + 1, r, ql, qr, x + x + 2);
   return max(left, right);
}

void solve() {
   for (int i = 0; i < 4 * n; ++i) seg[i] = 0;
   for (int i = 0; i <= n; ++i) dp[i] = 0;

   for (int i = 1; i <= n; ++i)
      dp[h[i]] = v[i];

   for (int i = 1; i <= n; ++i) {
      ll mx_val = query(1, n, 1, h[i]-1, 0);
      dp[h[i]] = max(dp[h[i]], mx_val + v[i]);
      modify(1, n, h[i], 0, dp[h[i]]);
   }

   ll ans = 0;
   for (int i = 1; i <= n; ++i) {
      ans = max(dp[i], ans);
   }
   cout << ans << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n;
   for (int i = 1; i <= n; ++i) cin >> h[i];
   for (int i = 1; i <= n; ++i) cin >> v[i];
   solve();

   return EXIT_SUCCESS;
}
