/* author: Priyanshu Shrivastav, from IIT Palakkad *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define se second
#define fi first
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define Sqr(x) ((x)*(x))
#define Mod(x) ((x)%_mod)
#define inf (0x7fffffff)
#define eps ((double)1e-9)
#define maxn ((int)1e5+10)

typedef long long ll;

const int _mod = (int)1e9 + 7;

inline ll solve (ll n, ll x) {
  return (n*(n - 1))/2 - x;
}


int main() {
#ifdef CONVICTION
	 freopen ("in", "r", stdin);
#endif
	 ios_base::sync_with_stdio(false);
	 cin.tie (NULL); cout.precision (10); cout << fixed;

	 /*solution starts here...*/
	 int t;
	 cin >> t;
	 while (t--) {
		int n, a_i;
		cin >> n;
		vector <int> even_v;
		vector <int> odd_v;
		vector < pair <int, int> > p_even;
		vector < pair <int, int> > p_odd;

		for (int i = 0; i < n; ++i) {
		  cin >> a_i;
		  if (a_i & 1) odd_v.pb(a_i);
		  else even_v.pb(a_i);
		}

		sort (all (even_v));
		sort (all (odd_v));


		for (int i = 0, j = 1, k = 0; i < (int)even_v.size(); ++i)
		{
		  j = i + 1;
		  p_even.pb ({1, even_v[i]});
		  while (j < (int)even_v.size() && even_v[i] == even_v[j]) {
			 ++p_even[k].fi;
			 ++j;
		  }
		  ++k;
		  i = j - 1;
		}

		for (int i = 0, j = 1, k = 0; i < (int)odd_v.size(); ++i)
		{
		  j = i + 1;
		  p_odd.pb ({1, odd_v[i]});
		  while (j < (int)odd_v.size() && odd_v[i] == odd_v[j]) {
			 ++p_odd[k].fi;
			 ++j;
		  }
		  ++k;
		  i = j - 1;

		}

		ll x, y, cnt_x, cnt_y;
		cnt_x = cnt_y = x = y = 0;

		for (int i = 0; i < (int) p_even.size() - 1; ++i) {
		  int l = p_even[i].se >> 2;
		  int r = p_even[i + 1].se >> 2;
		  if (p_even[i].se + 2 == p_even[i + 1].se && l == r) {
			 x += (1ll * p_even[i].fi * p_even[i + 1].fi);
		  }
		}

		for (int i = 0; i < (int) p_odd.size() - 1; ++i) {
		  int l = p_odd[i].se >> 2;
		  int r = p_odd[i + 1].se >> 2;
		  if (p_odd[i].se + 2 == p_odd[i + 1].se && l == r) {
			 y += (1ll * p_odd[i].fi * p_odd[i + 1].fi);
		  }
		}
		for (int i = 0; i < (int)p_even.size(); ++i)
		  if (p_even[i].fi > 1) x += solve ((ll)p_even[i].fi, 0);

		for (int i = 0; i < (int)p_odd.size(); ++i)
		  if (p_odd[i].fi > 1) y += solve ((ll)p_odd[i].fi, 0);

		ll ans = solve ((ll)even_v.size(), (ll) x) + solve ((ll)odd_v.size(), (ll) y);
		cout << ans << '\n';
	 }
	 return 0;
}


