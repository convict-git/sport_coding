/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */
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

const int MAXN = 1e2 + 10;
const int _mod = 1e9 + 7;
int Ar[MAXN + 1] = {0};
void init (int N) { for (int i = 0; i < N + 1; ++i) Ar[i] = 0; }
void upd (int l, int r) { Ar[l] += 1, Ar[r + 1] -= 1;}
/*
int st [4 * maxn] = {0}, lz [4 * maxn] = {0};
inline int mid (int s, int e) { return s + ((e - s) >> 1); }
void upd (int s, int e, int qs, int qe, int x) {
	 if (lz [x] != 0) {
		  st [x] += lz [x];
		  if (s != e) {
				lz [x + x + 1] += lz [x];
				lz [x + x + 2] += lz [x];
		  }
		  lz [x] = 0;
	 }
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
*/
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
        init(n);
		//for (int i = 0; i < 4 * maxn; ++i) st [i] = lz [i] = 0; 
		for (int i = 0; i < (int)s.size(); ++i) {
			 if (s[i] == '.') continue;
			 else {
				  k =  (int) s[i] - '0';
				  l = max (0, i - k);
				  r = min ((int)s.size() - 1, i + k);
				  upd (l, r);
				  //upd (0, n - 1, l, r, 0);
			 }
		}
	//	int fval = st [0] + lz [0];
	//	if (fval >= 2) cout << "unsafe\n";
	//	else cout << "safe\n";
	    bool ok = false;
	    for (int i = 0; i < n; ++i) {
	        if (i) Ar[i] += Ar[i - 1];
	        if (Ar[i] >= 2) {
	            cout << "unsafe\n";
	            ok = true;
	            break;
	        }
	    }
	    if (!ok)cout << "safe\n";
  }
  return 0;
}