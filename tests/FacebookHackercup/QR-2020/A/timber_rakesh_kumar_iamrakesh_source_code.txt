#include <iostream>
#include <set>
#include <vector>
#include <map>

// No need for long long,
// 2e9 is in the integer range
// But for self satisfaction
// I have used long long
typedef long long ll;
using namespace std;

const int N = 5e6;
set <ll> points;
map <ll, int> mp;
map <ll, ll> logg;
map <ll, vector <ll>> tim;
vector <ll> vec;
ll dp[N][2];

void init() {
  mp.clear();
  logg.clear();
  tim.clear();
  vec.clear();
  points.clear();
}

int main() {
  int t;
  scanf("%d", &t);
  for (int h = 0; h < t; ++h) {
    int n;
    scanf("%d", &n);
    init();
    for (int i = 0; i < n; ++i) {
      ll pi, hi;
      scanf("%lld%lld", &pi, &hi);
      points.insert(pi + hi);
      points.insert(pi - hi);
      points.insert(pi);
      logg[pi] = hi;
      if (tim.find(pi - hi) == tim.end())
	tim[pi - hi] = vector <ll> {pi};
      else
	tim[pi - hi].push_back(pi);
    }
    int size = 0;
    for (ll v : points) {
      vec.push_back(v);
      mp[v] = size++;
    }
    ll ans = 0;
    for (int i = size - 1; i >= 0; i--) {
      ll val = vec[i];
      // 0
      dp[i][0] = 0;
      if (tim.find(val) != tim.end()) {
	for (auto v : tim[val]) {
	  int ind = mp[v];
	  dp[i][0] = max(dp[i][0], dp[ind][0] + v - val);
	}
      }
      ans = max(ans, dp[i][0]);
      // 1
      dp[i][1] = 0;
      if (logg.find(val) == logg.end())
	continue;
      ll hi = logg[val];
      int ind = mp[val + hi];
      dp[i][1] = max(dp[i][1], max(dp[ind][0], dp[ind][1]) + hi);
      ans = max(ans, dp[i][1]);
    }
    printf("Case #%d: %lld\n", h + 1, ans);
  }
  return 0;
}
