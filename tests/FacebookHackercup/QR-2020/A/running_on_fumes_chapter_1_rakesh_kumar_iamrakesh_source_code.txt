#include <iostream>

typedef long long ll;
using namespace std;

const int N = 1e6 + 5;
const ll inf = 1e17;
ll t[N << 2], ci[N];

void build(int n) {
  for (int i = 0; i < 4 * n; ++i)
    t[i] = 0;
  return;
}

void update(int v, int tl, int tr, int pos, ll val) {
  if (tl == tr) {
    t[v] = val;
    return;
  }
  int mid = (tl + tr) >> 1;
  if (pos <= mid)
    update(2 * v + 1, tl, mid, pos, val);
  else
    update(2 * v + 2, mid + 1, tr, pos, val);
  t[v] = min(t[2 * v + 1], t[2 * v + 2]);
}

ll query(int v, int tl, int tr, int l, int r) {
  if (l > r)
    return inf;
  if (tl == l && tr == r)
    return t[v];
  int mid = (tl + tr) >> 1;
  return min(query(2 * v + 1, tl, mid, l, min(r, mid)),
	     query(2 * v + 2, mid + 1, tr, max(l, mid + 1), r));
}

int main() {
  int t;
  scanf("%d", &t);
  for (int h = 0; h < t; ++h) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
      scanf("%lld", ci + i);
    ci[0] = 1;
    build(n);
    for (int i = n - 2; i >= 0; i--) {
      if (ci[i] == 0) {
	update(0, 0, n - 1, i, inf);
	continue;
      }
      ll dp = query(0, 0, n - 1, i + 1, min(i + m, n - 1));
      if (i)
	dp += ci[i];
      if (dp >= inf)
	dp = inf;
      //cout<<dp<<" "<<i+1<<endl;
      update(0, 0, n - 1, i, dp);
    }
    ll ans = query(0, 0, n - 1, 0, 0);
    printf("Case #%d: ", h + 1);
    if (ans >= inf)
      puts("-1");
    else
      printf("%lld\n", ans);
  }
  return 0;
}
