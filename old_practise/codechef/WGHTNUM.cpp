/*author* Priyanshu Shrivastav
*from*(IIT Palakkad)
 *_ __ ___  _ ______ ___  _ ____   ___  ___| |_
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
 * Now, only God knows*/

#include <bits/stdc++.h>
#include <ctime>
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

ull modit (ull a, ull n) {
	 ull k = 1;
	 while (n) {
		  if (n&1)
				k = mod(k*a);
		  a = mod(sqr(a));
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
		 ull n, c = 0;
		 int w;
		 cin >> n >> w;

		 for (int i = 0; i < 10; i++)
			  for (int j = 1; j < 10; j++)
					i - j == w ? c++ : c;

		 c = mod (c*modit (10, n-2));
		 cout << c << '\n';
	}

	return 0;
}

