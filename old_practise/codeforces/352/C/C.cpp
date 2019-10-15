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
#define SQR(x) ((x)*(x))
#define MOD(x) ((x)%_mod)
#define INF (_mod-7)
#define EPS ((ld)1e-9)
#define MAXN ((int)1e5+10)

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

const ui _mod = (ui)1e9 + 7;
ld N[4001], D[4001], Ans[4001];

bool comp (ld p, ld q) {
  return (p - floor (p)) < (q - floor (q));
}

int main() {
#ifdef CONVICTION
	 freopen ("input2", "r", stdin);
#endif
	 ios_base::sync_with_stdio(false);
	 cin.tie (NULL); cout.precision (3); cout << fixed;

	 /*solution starts here...*/
	 int n, cN, cD;
	 cN = cD = 0;
	 cin >> n;
	 double diff = 0.000;

	 for (int i = 0; i < 2*n; i++) {
		double k;
		cin >> k;
		if (floor (k) == ceil (k)) N[cN++] = k;
		else D[cD++] = k;
	 }
	 sort (D, D + cD, comp);

	 int i = 0, j = 0, k = 0;
	 while (D[j] - floor (D[j]) <= 0.5) {
		Ans [i++] = D[j++];
	 }
	 while (cN--) {
		Ans [i++] = N[k++];
	 }
	 while (j < cD) {
		Ans[i++] = D[j++];
	 }

	 //for (int i = 0; i < 2*n; i++) cout << Ans [i] << " \n" [i == 2*n - 1];
	 for (int i = 0; i < n; i++)
		diff += abs (floor (Ans [i]) - Ans [i] + ceil (Ans[2*n - i - 1]) - Ans[2*n - i - 1]);

	 cout << diff << '\n';
	 return 0;
}
