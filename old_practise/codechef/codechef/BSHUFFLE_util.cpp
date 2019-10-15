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

vector < vector <int> > p;

void solve (vector <int> v1, int x, int n) {
  if (x == n) return;
  if (x == n) return;
  for (int i = 0; i < n; ++i) {
	 swap (v1[x], v1[i]);
	 if (x == n - 1) p.pb (v1);

	 solve (v1, x + 1, n);
	 swap (v1[x], v1[i]);
  }
}
vector <pair <int, vector <int> >> ps;

int main() {
#ifdef CONVICTION
	 freopen ("in", "r", stdin);
#endif
	 ios_base::sync_with_stdio(false);
	 cin.tie (NULL); cout.precision (10); cout << fixed;

	 /*solution starts here...*/
	 int n = 7;

	 vector <int> v;
	 for (int i = 1; i <= n; ++i) v.pb (i);
	 solve (v, 0, n);
	 sort (all (p));

	 int count = 1;
	 for (int i = 0, j = i + 1; i < (int) p.size() - 1; ) {
		count = 1;
		while (j < (int) p.size() && p[i] == p[j]) {
		  ++count;
		  ++j;
		}
		ps.pb ({count, p[i]});
		i = j, j = i + 1;
	 }

	 sort (all (ps));
	 for (auto it : ps[ps.size() - 1].se) cout << it << ' '; cout << '\n';
	 for (auto it : ps[0].se) cout << it << ' '; cout << '\n';
	 return 0;
}

