/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */
#include         <iostream>
#include         <algorithm>
#include         <cstdlib>
#include         <cmath>
#include         <vector>
#include         <set>
#include         <string>
#include         <climits>
#include         <map>
#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define bug(s,x) fprintf(stderr,"[%s %s : %i]\n",s,#x,x)
#define bg(x)    bug ("here : ", x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
#define IOS      ios_base::sync_with_stdio(false)
#define PREC     cin.tie (NULL); cout.precision (10); cout << fixed;
using namespace std;
int warnscanf_shit;
typedef int64_t ll;
typedef uint64_t ull;
const int maxn = 2e5 + 10;
const int _mod = 1e9 + 7;
struct cc { int x, y, r; };
int n, q, k, x, y, r;
cc cir[maxn];
int lzfq[maxn] = {0};

bool comp (cc c1, cc c2) { return c1.r < c2.r; }
/*
ll st[10 * maxn + 10] = {0};
inline int mid (int s, int e) {return s + ((e - s)>>1); }
void upd (int s, int e, int qs, int qe, int x) {
  if (s > qe || e < qs) return;
  else if (s >= qs && e <= qe) {
	 ++st[x];
	 return;
  }
  upd (s, mid (s, e), qs, qe, x + x + 1);
  upd (mid (s, e) + 1, e, qs, qe, x + x + 2);
}
int qry (int s, int e, int q, int x) {
  if (s > q || e < q) return 0;
  if (s == e && s == q) return st[x];
  if (s <= q && e >= q && s != e) {
	 return st[x] + qry (s, mid (s, e), q, x + x + 1) + qry (mid (s, e) + 1, e, q, x + x + 2);
  }
  else return 0;
}
*/

ll dcsq (cc c1, cc c2) {
  return 1LL * (c1.x - c2.x) * (c1.x - c2.x) + 1LL * (c1.y - c2.y) * (c1.y - c2.y);
}

bool out (cc c1, cc c2) { return floor (sqrtl(dcsq(c1, c2))) >= c1.r + c2.r; }
bool in (cc c1, cc c2) { return ceil (sqrtl(dcsq(c1, c2))) + c1.r <= c2.r; } //TODO why? ceil nd not floor

int mX (cc c1, cc c2) {
  return (int)floor(sqrtl(dcsq(c1, c2))) + c1.r + c2.r;
}

int mI (cc c1, cc c2) {
  if (out (c1, c2)) return max (0, (int)ceil (sqrtl(dcsq(c1, c2))) - c1.r - c2.r); //TODO
  else if (in (c1, c2)) return max (0, c2.r - (int)floor (sqrtl(dcsq(c1, c2))) - c1.r); //TODO
  return 0;
}

int main() {
	 //IOS; PREC;
#ifdef CONVICTION
	 if(!freopen ("in", "r", stdin)) return EXIT_FAILURE;
#endif
	 scanf (" %i%i", &n, &q);
	 for (int i = 0; i < n; ++i) {
		scanf (" %i%i%i", &x, &y, &r);
		cir[i] = {x, y, r};
	 }
	 sort (cir, cir + n, comp);  //now c1 is smaller than or equal to c2

	 for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
		  int mxidx = mX (cir[i], cir[j]);
		  int miidx = mI (cir[i], cir[j]);
		  //printf ("mi %i mx %i\n", miidx, mxidx);
		  //upd (0, maxn, miidx, mxidx, 0);
		  ++lzfq[miidx];
		  --lzfq[mxidx + 1];
		}
	 }
	 for (int i = 1; i < maxn; ++i)
		lzfq[i] += lzfq[i - 1];

	 while (q--) {
		scanf (" %i", &k);
		//printf ("%i\n", qry (0, maxn, k, 0));
		printf ("%i\n", lzfq[k]);
	 }
	 return EXIT_SUCCESS;
}

