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

int main() {
#ifdef CONVICTION
	 freopen ("in", "r", stdin);
#endif
	 ios_base::sync_with_stdio(false);
	 cin.tie (NULL); cout.precision (10); cout << fixed;

	 /*solution starts here...*/
	 int t;
	 cin >> t;
	 ll n, m, x, y;
	 while (t--) {
		cin >> n >> m >> x >> y;
		bool b1, b2;
		b1 = b2 = false;

		if ((n - 1)%x == 0 && (m - 1)%y == 0) b1 = true;
		if (m > 1 && n > 1 && (n - 2)%x == 0 && (m - 2)%y == 0) b2 = true; //share chat
		cout << (b1 or b2 ? "Chefirnemo\n" : "Pofik\n");
	 }
	 return 0;
}
