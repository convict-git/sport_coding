//I know the solution is wrong
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
#define bug(s,x) fprintf(stderr,"%s %s : %i\n",s,#x,x)
#define bg(x)    fprintf(stderr,"%s : %i\n",#x,x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
int warnscanf_shit;


typedef int64_t ll;
typedef uint64_t ull;

const int maxn = 1e5 + 10;
const int _mod = 1e9 + 7;
int t, n, k, sm, ltk;
int A[maxn];
int check (int val, int g) {
	 return ((val + A[n - 1] - g) % 2 == 0 ? 1 : 0);
}
int ls (int l, int h, int sm) {
	 int fval = -1;
	 for (int i = h; i >= l; --i) {
		  if (check (sm, i)) {
				fval = i;
				return fval;
		  }
	 }
	 return fval;
}
int solve (int p, int q, int sm) {
	 sm -= (q - p + 1) * k;
	 int L = k;
	 int H = A [n - 1];
	 return ls (L, H, sm);
}
int main() {
#ifdef CONVICTION
  if(!freopen ("in", "r", stdin)) return -1;
#endif
  //ios_base::sync_with_stdio(false);
  //cin.tie (NULL); cout.precision (10); cout << fixed;
  /*solution starts here...*/
  scanf ("%i", &t);
  while (t--) {
		scanf ("%i%i", &n, &k);
		for (int i = 0; i < n; ++i)
			 scanf ("%i", A + i);
		sort (A, A + n);

		sm = ltk = 0;
		int p = -1, q = n - 2;
		for (int i = 0; i < n - 1; ++i) {
			 if (A[i] > k) {
				  p == -1 ? p = i : p;
				  sm += A[i];
			 }
			 else ltk += A[i];
		}
		if (p != -1) {
			 int fval = solve (p, q, sm);
			 sm = ltk + (q - p + 1) * k + fval;
		}
		else sm = ltk + A[n - 1];
		printf ("%i\n", sm);
  }
  return 0;
}
