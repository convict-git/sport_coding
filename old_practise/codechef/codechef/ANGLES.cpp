#include         <bits/stdc++.h>
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
const int _mod = 1e9 + 7;
const int maxn = 1e3 + 10;

struct el {
  int x, y;
  ll val;
  bool operator < (const el p) {
	 return (x < p.x || (x == p.x && val < p.val));
  }
};

int lb (el * a, el* b, ll k, el* S) {
  el* g = a + ((b-a)>>1);
  if (b < a) return -1;
  else if (g->val == k) {
	 if ((g + 1 < b && (g + 1)->val > k) || g == b - 1) return g - S;
	 else return lb (g + 1, b, k, S);
  }
  else if (g->val > k) {
	 if (g - 1 >= a && (g - 1)->val == k) return g - 1 - S;
	 else if (g == a || g - 1 >= a && (g - 1)->val < k) return g - S;
	 else return lb (a, g - 1, k, S);
  }
  else {
	 if (g + 1 < b && (g + 1)->val > k) return g + 1 - S;
	 else return lb (g + 1, b, k, S);
  }
}

inline ll fn (int x, int z, int p, int q) {
  return 1LL*q*(1LL*x*x + 1LL*z*z) - 1LL*2*p*x*z;
}
int A[maxn];
el Sq[4 * maxn * maxn];

void solve () {
  memset (A, 0, sizeof A);
  memset (Sq, 0, sizeof Sq);
  int n, p, q, sq_c;
  scanf ("%i%i%i", &n, &p, &q);
  sq_c = 0;
  for (int i = 0; i < n; ++i) {
	 scanf ("%i", A + i);
  }

  for (int i = 0; i < n - 1; ++i)  {
	 for (int j = i + 1; j < n; ++j) {
		Sq[sq_c]= {i, j, fn (A[i], A[j], p, q)};
		++sq_c;
	 }
  }

  sort (Sq, Sq + sq_c);
  //for (int i = 0; i < sq_c; ++i) { fprintf (stderr, "x : %i, y : %i, val : %ld, A[x] : %i, A[y] : %i, p %i, q %i\n", Sq[i].x, Sq[i].y, Sq[i].val, A[Sq[i].x], A[Sq[i].y], p, q); }

  bool ok = false;
  for (int k = 0; k < n; ++k) {
	 ll key = 1LL * q * A[k]; //find lower bound for this

	 for (int sb = 0; sb < n; ++sb) {
		int y_idx, x_idx, z_idx;
		y_idx = x_idx = z_idx = -1;
		//fprintf (stderr, "key %ld k %i sb %i\n", key, k, sb);
		if (sb == k) continue; //correct

		int idx = lb (Sq + (n - 1)*sb, Sq + (n - 1)*(sb + 1), key, Sq + (n - 1)*sb); //lower_bound
		if (idx == -1) continue;
		int _idx_real = idx + (n - 1)*sb;

		//fprintf (stderr, "_idx_real %i\n", _idx_real);
		while (_idx_real < idx + (n - 1)*(sb + 1)) {
		  //fprintf (stderr, "A[k] %i  A[Sq[_idx_real].x] %i  A[Sq[_idx_real].y %i\n", A[k], A[Sq[_idx_real].x], A[Sq[_idx_real].y]);
		  if (Sq[_idx_real].y == k) {
			 ++_idx_real;
			 continue;
		  }
		  bool c1 =  A[k] < A[Sq[_idx_real].x] + A[Sq[_idx_real].y];
		  bool c2 =  A[k] + A[Sq[_idx_real].x] > A[Sq[_idx_real].y];
		  bool c3 = A[k] + A[Sq[_idx_real].y] > A[Sq[_idx_real].x];
		  if (c1 & c2 & c3) {
			 z_idx = k;
			 x_idx = Sq[_idx_real].x;
			 y_idx = Sq[_idx_real].y;
			 ok = true;
			 //fprintf (stderr, "Yehe!! ok is true!!\n");
			 break;
		  }
		  ++_idx_real;
		}

		if (ok) {
		  ++y_idx, ++x_idx, ++z_idx;
		  int id[3] = {y_idx, x_idx, z_idx};
		  sort (id, id + 3);
		  printf ("%i %i %i\n", id[0], id[1], id[2]);
		  return;
		}
	 }
  }
  if (!ok) printf ("-1\n");
}

int main() {
  //IOS; PREC;
#ifdef CONVICTION
  if(!freopen ("in", "r", stdin)) return EXIT_FAILURE;
#endif
  int tc;
  scanf ("%i", &tc);
  while (tc--) {
	 solve();
  }
  return EXIT_SUCCESS;
}

