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
const int maxn = 2e6 + 10;

int pr[maxn], sz[maxn], rnk[maxn];
ll st[4 * maxn] = {0};
inline int mid (int s, int e) { return s + ((e - s) >> 1); }

void upd (int s, int e, int q, int x, int k) { //logn
	 if (e < q || s > q) return;
	 if (s >= q && e <= q && s == e) {
		  st[x] += k;
		  return;
	 }
	 upd (s, mid (s, e), q, x + x + 1, k);
	 upd (mid (s, e) + 1, e, q, x + x + 2, k);
	 st[x] = st[x + x + 1] + st[x + x + 2];
}

ll gets (int s, int e, int qs, int qe, int x) { //logn
	 if (e < qs || s > qe) return 0;
	 if (s >= qs && e <= qe) return st[x];
	 ll lgets = gets (s, mid (s, e), qs, qe, x + x + 1);
	 ll rgets = gets (mid (s, e) + 1, e, qs, qe, x + x + 2);
	 return lgets + rgets;
}

void createset (int x) {
  pr[x] = x;
  rnk[x] = 0;
  sz[x] = 1;
}

int findset (int x) { //logn
  while (x != pr[x]) x = pr[x];
  return x;
}

void merge (int x, int y, int n) {//logn
  int repx = findset (x);
  int repy = findset (y);
  int szx = sz[repx];
  int szy = sz[repy];
  if (rnk[repx] > rnk[repy])  {
	 pr[repy] = repx;
	 sz[repx] += sz[repy];
	 sz[repy] = 0;
  }
  else {
	 pr[repx] = repy;
	 sz[repy] += sz[repx];
	 sz[repx] = 0;
  }
  if (rnk[repx] == rnk[repy])
	 ++rnk[repy];
  upd (0, n - 1, szx, 0, -1);
  upd (0, n - 1, szy, 0, -1);
  upd (0, n - 1, szx + szy, 0, 1);
}

int n, q, u, v;
char s[8];
int main() {
	 //IOS; PREC;
	 scanf ("%i%i", &n, &q);
	 for (int i = 0; i < n; ++i)
		createset (i);
	 upd (0, n - 1, 1, 0, n);

	 while (q--) {
		scanf (" %s", s);
		if (strcmp (s,"Charlie") == 0) {
		  scanf ("%i%i", &u, &v);
		  merge (u, v, n);
		}
		else if (strcmp (s, "Bravo") == 0) {
		  scanf ("%i%i", &u, &v);
		  ll getme = gets (0, n - 1, u, v, 0);
		  printf ("%lld\n", getme);
		}
		else assert (false);
	 }
	 return EXIT_SUCCESS;
}


