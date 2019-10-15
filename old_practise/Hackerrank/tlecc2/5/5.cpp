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
const int MAXN = 2e6+ 10;
char buffer[100];
int Ar[MAXN];
ll st[4 * MAXN];
inline int mid (int s, int e) { return (s + e)>>1; }

void create (int s, int e, int x) {
  if (s == e) {
	 st[x] = Ar[s];
	 return;
  }
  create (s, mid (s, e), x + x + 1);
  create (mid (s, e) + 1, e, x + x + 2);
  st[x] = st[x + x + 1] + st[x + x + 2];
}

void upd (int s, int e, int q, int x) {
  if (s > q || e < q) return;
  if (q >= s && q <= e && s == e) {
	 st[x] ^= 1;
	 return;
  }
  upd (s, mid (s, e), q, x + x + 1);
  upd (mid (s, e) + 1, e, q, x + x + 2);
  st[x] = st[x + x + 1] + st[x + x + 2];
}

ll gets (int s, int e, int qs, int qe, int x) {
  if (s > qe || e < qs) return 0;
  if (s >= qs && e <= qe) {
	 return st[x];
  }
  ll lgets = gets (s, mid (s,e), qs, qe, x + x + 1);
  ll rgets = gets (mid(s,e) + 1, e, qs, qe, x + x + 2);
  return lgets + rgets;
}

int kth (int s, int e, int k, int x) {
  if (s == e) {
	 return s;
  }
  int l = st[x + x + 1];
  if (l >= k) {
	 return kth (s, mid (s,e), k, x + x + 1);
  }
  else {
	 return kth (mid (s, e) + 1, e, k - l, x + x + 2);
  }
}

int n, q, l, r, p, k, t;
int main() {

	 //IOS; PREC;
	 scanf ("%i%i", &n, &q);
	 for(int i = 0; i < n; ++i) {
		  scanf("%i",&Ar[i]);
		  Ar[i] ^= 1;
	 }
	 create (0, n - 1, 0);


	 while(q--)
	 {
		scanf (" %i", &t);
		if (t == 1) {
		  scanf (" %i%i", &l, &r);
		  ll getme = gets (0, n - 1, l, r, 0);
		  printf ("%lld\n", getme);
		}
		else if (t == 2) {
		  scanf (" %i", &p);
		  upd (0, n - 1, p, 0);
		}
		else {
		  scanf (" %i", &k);
		  if (st[0] < k) printf ("-1\n");
		  else {
			 int kthme = kth (0, n - 1, k, 0);
			 printf ("%i\n", kthme);
		  }
		}
	 }
	 return EXIT_SUCCESS;
}


