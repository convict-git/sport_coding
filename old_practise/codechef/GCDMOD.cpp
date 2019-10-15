/*author* Priyanshu Shrivastav
*from*(IIT Palakkad)
 *_ __ ___  _ ______ ___  _ ____   ___  ___| |_
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
 * Now, only God knows*/

#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define se second
#define fi first
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sqr(x) ((x)*(x))
#define mod(x) ((x)%N)
#define INF (N-7)
#define EPS (long double)1e-9

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

const ui N = 1000000007;
const ui _N = 1000000;

ull multiply (ull k, ull a, ull m) {
	 ull x = k/_N;
	 ull y = k%_N;
	 return ((((_N*a)%m)*(x%m))%m + (y*a)%m)%m;
}

ull A_n (ull a, ull n, ull m) {
	 ull k = 1;
	 while (n) {
		  if (n&1)
				k = multiply (k%m, a%m, m);
		  a = multiply (a%m, a%m, m);
		  n = n >> 1;
	 }
	 return k;
}

int main() {
#ifdef CONVICTION
	FILE* fp_in = freopen ("in", "r", stdin);
#endif
	ios_base::sync_with_stdio(false);
	cin.tie (NULL); cout.precision (10); cout << fixed;

	/*solution starts here...*/

	int t;
	cin >> t;
	while (t--) {
		 ull a, b, n;
		 cin >> a >> b >> n;
		 ull k = (a > b ? a - b : b - a);

		 if (a == b)
			  cout << mod (A_n (a, n, N) + A_n (b, n, N)) << '\n';
		 else if (a - b == 1)
			  cout << 1 << '\n';
		 else {
			  a = A_n (a, n, k);
			  b = A_n (b, n, k);
			  a = (a + b)%k;
			  cout << __gcd (k, a) << '\n';
		 }
	}
	return 0;
}
