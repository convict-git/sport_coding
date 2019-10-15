/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <string>
#include <climits>
using namespace std;

#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define sqr(x)   ((x)*(x))
#define Mod(x)   ((x)%_mod)
#define bug(s,x) fprintf(stderr,"%s %s : %i\n",s,#x,x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
int warnscanf_shit;


typedef int64_t ll;
typedef uint64_t ull;

const int maxn = (int)2e6 + 10;
const int _mod = (int)1e9 + 7;
int n;
ll A[maxn], B [maxn];

int main() {
#ifdef CONVICTION
  if(!freopen ("in", "r", stdin)) return -1;
#endif
  //ios_base::sync_with_stdio(false);
  //cin.tie (NULL); cout.precision (10); cout << fixed;
  /*solution starts here...*/
  int t;
  scanf (" %i", &t);
  while (t--) {
		scanf (" %i", &n);
		for (int i = 0; i < n; ++i) {
			 scanf (" %ld" , A + i);
			 if (i) {
				  B[i] = A[i] - A[i - 1];
			 }
		}
		int i = 0;
		if (A[0] >= A[n - 1]) {
			 while (i < n - 1 && B[i] >= 0) ++i;
			 if (i == n - 1) printf ("YES\n");
			 else {
				  ++i;
				  while (i < n - 1 && B[i] >= 0) ++i;
				  if (i == n - 1) printf ("YES\n");
				  else printf ("NO\n");
			 }

		}
		else {
			 while (i < n - 1 && B[i] >= 0) ++i;
			 if (i == n - 1) printf ("YES\n");
			 else printf ("NO\n");
		}
  }


  return 0;
}
