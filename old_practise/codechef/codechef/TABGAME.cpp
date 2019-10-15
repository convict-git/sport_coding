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

int v[1001][1001];

int main() {
#ifdef CONVICTION
	 freopen ("in", "r", stdin);
#endif
	 ios_base::sync_with_stdio(false);
	 cin.tie (NULL); cout.precision (10); cout << fixed;

	 /*solution starts here...*/
	 int t, n, m, q, l, r;
	 string s1, s2;
	 v[0][0] = 9;
	 cin >> t;
	 while (t--) {
		cin >> s1 >> s2;
		m = (int) s1.size();
		n = (int) s2.size();

		for (int j = 1; j <= m; ++j)
		  v[0][j] = (int) s1[j - 1] - '0';

		for (int i = 1; i <= n; ++i)
		  v[i][0] = (int) s2[i - 1] - '0';


		for (int i = 1; i <= n; ++i) {
		  for (int j = 1; j <= m; ++j) {
			 if (v[i][j - 1] == 1 && v[i - 1][j] == 1) v[i][j] = 0;
			 else v[i][j] = 1;
		  }
		}

		  for (int k = 0; k <= m; ++k)
			 cout << "-----" << " \n"[ k == m];
		for (int i = 0; i <= n; ++i) {
		  for (int j = 0; j <= m; ++j) {
			 cout << "| " << v[i][j] << " |" << " \n"[ j == m ];
		  }
		  for (int k = 0; k <= m; ++k)
			 cout << "-----" << " \n"[ k == m];
		}

		/*
		cin >> q;
		while (q--) {
		  cin >> l >> r;
		  if (v[l][r] == 2) cout << "1";
		  else cout << "0";
		} cout << '\n';
		*/
	 }

	 return 0;
}
