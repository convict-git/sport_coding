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
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
int warnscanf_shit;


typedef int64_t ll;
typedef uint64_t ull;

const int maxn = 1e5 + 10;
const int _mod = 1e9 + 7;
int st [4 * maxn] = {0}, lz [4 * maxn] = {0};
inline int mid (int s, int e) { return s + ((e - s) >> 1); }
void lzupd (int s, int e, int x) {
	 if (lz [x] != 0) {
		  st [x] += lz [x];
		  if (s != e) {
				lz [x + x + 1] += lz [x];
				lz [x + x + 2] += lz [x];
		  }
		  lz [x] = 0;
	 }
}
void upd (int s, int e, int qs, int qe, int x) {
	 lzupd (s, e, x);
	 if (e < qs || s > qe) return;
	 if (s >= qs && e <= qe) {
		  ++st [x];
		  if (s != e) {
				++lz [x + x + 1];
				++lz [x + x + 2];
		  }
		  return;
	 }
	 upd (s, mid (s, e), qs, qe, x + x + 1);
	 upd (mid (s, e) + 1, e, qs, qe, x + x + 2);
	 st [x] = max (st [x + x + 1], st [x + x + 2]);
}

int A[maxn];
int solve (int s, int e, int x) {
	if (e < s) return 0;
	int l = solve (s, e - 1, x + 1) + A[e]*x;
	int r = solve (s + 1, e, x + 1) + A[s]*x;
	return max (l, r);
}

int main() {
#ifdef CONVICTION
  if(!freopen ("in", "r", stdin)) return -1;
#endif
  ios_base::sync_with_stdio(false);
  cin.tie (NULL); cout.precision (10); cout << fixed;
  /*solution starts here...*/
  int t, n, k, l, r;
  string s;
  cin >> t;
  while (t--) {
		cin >> s;
		n = (int)s.size();
		for (int i = 0; i < 4 * maxn; ++i) st [i] = lz [i] = 0;
		for (int i = 0; i < (int)s.size(); ++i) {
			 if (s[i] == '.') continue;
			 else {
				  k =  (int) s[i] - '0';
				  l = max (0, i - k);
				  r = min ((int)s.size() - 1, i + k);
				  upd (0, n - 1, l, r, 0);
			 }
		}
		int fval = st [0] + lz [0];
		if (fval >= 2) printf ("unsafe\n");
		else printf ("safe\n");
  }

  return 0;
}

