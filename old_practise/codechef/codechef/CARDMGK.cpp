/*author* Priyanshu Shrivastav and Rakesh Kumar(from IIT Palakkad) *
 ****  __ _ ___ ___ _   _ _ __ ___   ___   /   \___  __ _  __| |****
 **** / _` / __/ __| | | | '_ ` _ \ / _ \ / /\ / _ \/ _` |/ _` |****
 ****| (_| \__ \__ \ |_| | | | | | |  __// /_//  __/ (_| | (_| |****
 *****\__,_|___/___/\__,_|_| |_| |_|\___/___,' \___|\__,_|\__,_|____
 |_____|                                                      |_____|
 *******************************************************************/


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
ll A[maxn];

int main() {
#ifdef CONVICTION
	 if(!freopen ("in", "r", stdin)) return -1;
#endif
	 //ios_base::sync_with_stdio(false);
	 //cin.tie (NULL); cout.precision (10); cout << fixed;
	 /*solution starts here...*/
	 int t, f, c;
	 scanf (" %i", &t);
	 while (t--) {
		  f = 0, c = 0;
		  scanf (" %i", &n);
		  for (int i = 0; i < n; ++i)
				scanf (" %ld", A + i);

		  int i = 0;
		  if (A[0] == A[n - 1]) f = 1;
		  if (A[0] <= A[n - 1]) {
				for (int ii = 0; ii < n - 1; ++ii) {
					 if (A[ii] > A[ii + 1]) {
						  c = 1;
						  if (f == 0) { printf ("NO\n");
								break;
						  }
						  else break;
					 }
				}
				if (c == 0) printf ("YES\n");
		  }
		  if ((f == 0 || c == 1) && A[0] >= A[n - 1]) {
				++i;
				while (i < n && A [i] >= A [i - 1] && A [i] >= A [n - 1])
					 ++i;
				if (A[i] > A[n - 1]) {
					 printf ("NO\n");
					 continue;
				}
				else {
					 ++i;
					 while (i < n && A [i] >= A [i - 1] && A [i] <= A [n - 1])
						  ++i;
					 if (i != n)
						  printf ("NO\n");
					 else printf ("YES\n");
				}
		  }
	 }
	 return 0;
}
