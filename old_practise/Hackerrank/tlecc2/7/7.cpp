#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <vector>
#include         <map>
#include         <set>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#pragma GCC      optimize ("Ofast")
#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define bug(s,x) fprintf(stderr,"[%s %s : %i]\n",s,#x,x),fflush(stderr)
#define bg(x)    bug ("bug : ", x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed

using namespace std;
int warnscanf_shit;
typedef long long ll;
typedef unsigned long long ull;
const int MOD = 1e9 + 7;
const int maxn = 2e5 + 10;
int Ao[maxn], Ae[maxn];
struct pnt {
	ll val;
	int idx;
};

pnt sto[4 * maxn], ste[4 * maxn];
ll  lzo[4 * maxn] = {0}, lze[4 * maxn] = {0};

inline int mid (int s, int e) { return (e + s)>>1; }
inline int leftLimitOdd (int x) { return (x + 1 - 2 * (x & 1))>>1; }
inline int leftLimitEven (int x) { return (x + (x & 1))>>1; }
inline int rightLimitOdd (int x) { return (x - 2 + (x & 1))>>1; }
inline int rightLimitEven (int x) { return (x - (x & 1))>>1; }

void create (int s, int e, int x, pnt* st, ll* lz, int* A) {
	lz[x] = 0;
	if (s == e) {
		st[x].val = A[s];
		st[x].idx = s;
		return;
	}
	create (s, mid (s, e), x + x + 1, st, lz, A);
	create (mid (s, e) + 1, e, x + x + 2, st, lz, A);
	st[x].val = max (st[x + x + 1].val, st[x + x + 2].val);
	st[x].idx = (st[x + x + 1].val > st[x + x + 2].val ?
			st[x + x + 1].idx : st[x + x + 2].idx);
}

void lzupd (int s, int e, int x, pnt* st, ll* lz) {
	if (lz[x] != 0) {
		st[x].val += lz[x];
		if (s != e) {
			lz[x + x + 1] += lz[x];
			lz[x + x + 2] += lz[x];
		}
		lz[x] = 0;
	}
}

void upd (int s, int e, int qs, int qe, int x, int k, pnt* st, ll* lz) {
	lzupd (s, e, x, st, lz);
	if (e < qs || s > qe) return;
	if (s >= qs && e <= qe) {
		st[x].val += k;
		if (s != e) {
			lz[x + x + 1] += k;
			lz[x + x + 2] += k;
		}
		return;
	}
	upd (s, mid (s, e), qs, qe, x + x + 1, k, st, lz);
	upd (mid (s, e) + 1, e, qs, qe, x + x + 2, k, st, lz);
	st[x].val = max (st[x + x + 1].val, st[x + x + 2].val);
	st[x].idx = (st[x + x + 1].val > st[x + x + 2].val
			? st[x + x + 1].idx : st[x + x + 2].idx);
}

pnt null = {LLONG_MIN, INT_MAX};
pnt gets (int s, int e, int qs, int qe, int x, pnt* st, ll *lz) {
	lzupd (s, e, x, st, lz);
	if (e < qs || s > qe) return null;
	if (s >= qs && e <= qe) return st[x];

	pnt lgets = gets (s, mid (s, e), qs, qe, x + x + 1, st, lz);
	pnt rgets = gets (mid (s, e) + 1, e, qs, qe, x + x + 2, st, lz);

	pnt ans;
	ans.val = max (lgets.val, rgets.val);
	if (lgets.val == rgets.val) {
		ans.idx = (lgets.idx < rgets.idx ? lgets.idx : rgets.idx);
	}
	else
		ans.idx = (lgets.val > rgets.val ? lgets.idx : rgets.idx);
	return ans;
}
vector <int> vi;
vector < pair <pair <int, int>, int>> vpp;
int n, q, no, ne;
int main() {
	//IOS; PREC;
	for (int i = 0; i < 4 * maxn; ++i) {
		lze[i] = lzo[i] = 0;
	}

	scanf ("%i%i", &n, &q);
	no = n/2, ne = no + (n & 1);
	for (int i = 0, e = 0, o = 0; i < n; ++i) {
		int tmp;
		scanf ("%i", &tmp);
		if (i & 1) Ao[o++] = tmp;
		else Ae[e++] = tmp;
	}

	create (0, ne - 1, 0, ste, lze, Ae);
	create (0, no - 1, 0, sto, lzo, Ao);

	while (q--) {
		int idxans;
		int l, r, p, le, lo, re, ro;
		char win;
		scanf ("%i%i%i", &l, &r, &p);
		getchar(); win = getchar();
		le = leftLimitEven (l);
		lo = leftLimitOdd (l);
		re = rightLimitEven (r);
		ro = rightLimitOdd (r);

		if (win == 'E') {
			upd (0, no - 1, lo, ro, 0, -1*p, sto, lzo);
			upd (0, ne - 1, le, re, 0, p, ste, lze);
		}
		else if (win == 'O') {
			upd (0, no - 1, lo, ro, 0, p, sto, lzo);
			upd (0, ne - 1, le, re, 0, -1*p, ste, lze);
		}
		else assert (false);

		pnt gete = gets (0, ne - 1, le, re, 0, ste, lze);
		pnt geto = gets (0, no - 1, lo, ro, 0, sto, lzo);
		if (gete.val > geto.val) {
			idxans = 2*gete.idx;
		}
		else if (gete.val < geto.val) {
			idxans = 2*geto.idx + 1;
		}
		else {
			idxans = (2*geto.idx + 1 < 2*gete.idx ? 2*geto.idx + 1 : 2*gete.idx);
		}
		printf ("%i\n", idxans);
	}
	printf ("\n");

	for (int i = 0; i < n; ++i) {
		pnt score;
		if (n & 1) {
			score = gets (0, no - 1, (i - 1)/2, (i - 1)/2, 0, sto, lzo);
		}
		else {
			score = gets (0, ne - 1, i/2, i/2, 0, ste, lze);
		}
		printf ("%lld\n", score.val);
	}

	return EXIT_SUCCESS;
}
