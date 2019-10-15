/* author: Priyanshu Shrivastav, from IIT Palakkad *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <climits>

using namespace std;

#define pb push_back
#define eb emplace_back
#define se second
#define fi first
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define Sqr(x) ((x)*(x))
#define Mod(x) ((x)%_mod)
#define inf (0x7fffffff)
#define eps ((double)1e-9)

typedef int64_t ll;
typedef uint64_t ull;

const int maxn = (int)2e6 + 10;
const int _mod = (int)1e9 + 7;
void solve (int n) {
	 int a, b, l, n_ref, m, i;
	 i = a = b = l = 0, n_ref = n;
	 int c = __builtin_popcount (n);
	 if (c == 2) printf ("%i\n", 0);
	 else if (c == 1)
		  printf ("%i\n", (n & 1 ? 2 : 1));
	 else {
		  c -= 2;
		  while (c) {
				if (n & 1) c--;
				l++;
				n >>= 1;
		  }
		  m = n;
		  a = n >> 1, b = a >> 1;
		  if (a & 1 && b & 1) {
				m <<= l;
				printf ("%i\n", n_ref - m);
		  }
		  else {
				a = abs (n_ref - (m << l));
				m >>= 1;
				m |= 1;
				m <<= (l + 1);
				b = abs (n_ref - m);
				for (i = 0; n_ref >= (1 << i); i++);
				c = abs (n_ref - ((1 << i) | 1));
				printf ("%i\n", min (min (a, b), c));
		  }
	 }
	 return;
}

int main() {
#ifdef CONVICTION
	 if (!freopen ("in", "r", stdin)) return - 1;
#endif
	 //ios_base::sync_with_stdio(false);
	 //cin.tie (NULL); cout.precision (10); cout << fixed;

	 /*solution starts here...
	  */
	 int t, n;
	 scanf (" %i", &t);
	 while (t--) {
		  scanf (" %d", &n);
		  solve (n);
	 }

	 return 0;
}


