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

int A[maxn];
ll st[4 * maxn], lz[4 * maxn];
inline int mid (int s, int e) { return s + ((e - s) >> 1); }

void create (int s, int e, int x) {
	 lz[x] = 0;
	 if (s == e) {
		  st[x] = A[s];
		  return;
	 }
	 create (s, mid (s, e), x + x + 1);
	 create (mid (s, e) + 1, e, x + x + 2);
	 st[x] = st[x + x + 1] + st[x + x + 2];
}
void lzupd (int s, int e, int x) {
	 if (lz[x] != 0) {
		  st[x] += lz[x] * (e - s + 1);
		  if (s != e) {
				lz[x + x + 1] += lz[x];
				lz[x + x + 2] += lz[x];
		  }
		  lz[x] = 0;
	 }
}
void upd (int s, int e, int qs, int qe, int x, int k) {
	 lzupd (s, e, x);
	 if (e < qs || s > qe) return;
	 if (s >= qs && e <= qe) {
		  st[x] += k * (e - s + 1);
		  if (s != e) {
				lz[x + x + 1] += k;
				lz[x + x + 2] += k;
		  }
		  return;
	 }
	 upd (s, mid (s, e), qs, qe, x + x + 1, k);
	 upd (mid (s, e) + 1, e, qs, qe, x + x + 2, k);
	 st[x] = st[x + x + 1] + st[x + x + 2];
}
ll gets (int s, int e, int qs, int qe, int x) {
	 lzupd (s, e, x);
	 if (e < qs || s > qe) return 0;
	 if (s >= qs && e <= qe) return st[x];
	 ll lgets = gets (s, mid (s, e), qs, qe, x + x + 1);
	 ll rgets = gets (mid (s, e) + 1, e, qs, qe, x + x + 2);
	 return lgets + rgets;
}
int main() {
	 //IOS; PREC;


	 return EXIT_SUCCESS;
}


