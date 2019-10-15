/*author : mr.convict (Priyanshu Shrivastav from IIT Palakkad) */
/*solution coded on ideone*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 10;
int Ar[MAXN];
struct node {
	int prx, sfx, mx;
	node(int x = 0) : prx(x), sfx(x), mx(x) {}
	node operator = (const node& p) { prx = p.prx, sfx = p.sfx, mx = p.mx;}
} ;
node st[4*MAXN];

inline int mid (int s, int e) { return s + ((e - s) >> 1); }

void form (int s, int e, int x) {
	if (s == e) {
		st[x].prx = st[x].sfx = st[x].mx = Ar[s];
		return;
	}
	form (s, mid(s,e), x + x + 1);
	form (mid (s,e) + 1, e, x + x + 2);
	
	st[x].prx = st[x + x + 1].prx;
	st[x].sfx = st[x + x + 2].sfx;
	if (st[x + x + 1].prx == (mid (s,e) - s + 1)) st[x].prx += st[x + x + 2].prx;
	if (st[x + x + 2].sfx == (e - mid (s,e))) st[x].sfx += st[x + x + 1].sfx;
	int mxChild = max (st[x + x + 1].mx, st[x + x + 2].mx);
	st[x].mx = max (mxChild, st[x + x + 1].sfx + st[x + x + 2].prx);
}

node qry(0); 

node getS (int s, int e, int qs, int qe, int x) {
	if (s > qe || e < qs) return qry;
	if (s >= qs && e <= qe) return st[x];
	else {
		node lft = getS(s, mid (s,e), qs, qe, x + x + 1);
		node rgt = getS(mid (s,e) + 1, e, qs, qe, x + x + 2);
		node mrg;
		
			mrg.prx = lft.prx;
			mrg.sfx = rgt.sfx;
			if (lft.prx == (mid(s,e) - s + 1)) mrg.prx += rgt.prx;
			if (rgt.prx == (e - mid (s,e))) mrg.sfx += lft.sfx;
			int mxChild = max (lft.mx, rgt.mx);
			mrg.mx = max (mxChild, lft.sfx + rgt.prx);
		
		return mrg;
	}
}
int N, Q, K;

int main() {
	scanf ("%i%i%i", &N, &Q, &K);
	for (int i = 0; i < N; ++i)
		scanf ("%i", Ar + i);
	for (int i = N; i < 2 * N; ++i)
		Ar[i] = Ar[i - N];
	form(0, (N<<1) - 1, 0);
	int L = 0;
	char ch; ch = getchar();
	while ((ch = getchar()) != EOF) {
		if (ch == '?') {
			node ans = getS(0, (N<<1) - 1, L, L + N - 1, 0);
			printf ("%i\n", min (K, ans.mx));
		}
		else if (ch == '!'){
			L = (L + N - 1)%N;
		}
	}
	return EXIT_SUCCESS;
}