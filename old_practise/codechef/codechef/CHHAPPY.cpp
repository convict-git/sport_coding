#include         <iostream>
#include         <algorithm>
#include         <cstdlib>
#include         <cmath>
#include         <vector>
#include         <set>
#include         <string>
#include         <climits>
#include  	     <cstring>
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
const int mod = 1e9 + 7;
const int maxn = 1e5 + 10;
int tc, n;
int A[maxn];

void solve () {
  scanf ("%i", &n);
  memset (A, 0, sizeof A);
  for (int i = 0; i < n; ++i)
	 scanf ("%i", A + i);
  vector < set <int> > s(n + 1);
  for (int i = 0; i < n; ++i) {
	 if (A[i] <= n)
		s[A[A[i] - 1]].insert (A[i]);
  }
  for (int i = 0; i < n; ++i)
	 if (s[i].size() > 1)  {
		printf ("Truly Happy\n");
		return;
	 }
  printf ("Poor chef\n");
}

int main() {
	 //IOS; PREC;
#ifdef CONVICTION
	 if(!freopen ("in", "r", stdin)) return EXIT_FAILURE;
#endif
	 scanf ("%i", &tc);
	 while (tc--)
		solve();
	 return EXIT_SUCCESS;
}

