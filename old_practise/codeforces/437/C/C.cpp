#include         <iostream>
#include         <algorithm>
#include         <functional>
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
const int mod = 1e9 + 7;
const int maxn = 1e3 + 10;
int n, m, sm, u, v;
int A[maxn];

int main() {
	 //IOS; PREC;
	 sm = 0;
	 scanf ("%i%i", &n, &m);
	 for (int i = 1; i <= n; ++i) {
		scanf ("%i", A + i);
	 }
	 for (int i = 0; i < m; ++i) {
		scanf ("%i%i", &u, &v);
		sm += min (A[u], A[v]);
	 }
	 printf ("%i\n", sm);
	 return EXIT_SUCCESS;
}
