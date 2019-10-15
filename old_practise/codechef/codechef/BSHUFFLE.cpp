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
	 int n;
	 cin >> n;
	 if (n == 1) {
		cout << 1 << '\n' << 1 << '\n';
		return 0;
	 }
	 for (int i = 2; i <= ceil(n/2.0); ++i)
		cout << i << ' ';

	 cout << 1 << ' ';

	 for (int i = ceil(n/2.0) + 2; i <= n; ++i)
		cout << i << ' ';
	 cout << (int)ceil (n/2.0) + 1 << '\n';

	 cout << n << ' ';
	 for (int i = 1; i <= n - 1; ++i)
		cout << i << " \n" [ i == n - 1];

	 return 0;
}

