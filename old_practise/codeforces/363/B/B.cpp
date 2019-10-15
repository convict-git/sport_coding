#include         <iostream>
#include         <algorithm>
#include         <functional>
#include         <vector>
#include         <map>
#include         <set>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
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
const int maxn = 1e6 + 10;
int n, k;
int h[maxn];
int dp[maxn];

int main() {
	 //IOS; PREC;
	 scanf ("%i%i", &n, &k);
	 for (int i = 0; i < n; ++i) {
		scanf (" %i", &h[i]);
		if (i) dp[i] = dp[i - 1] + h[i];
		else dp[i] = h[i];
	 }
	 int mn = dp[k-1], idx = k - 1;
	 for (int i = k; i < n; ++i) {
		if (mn > dp[i] - dp[i - k]) {
		  mn = dp[i] - dp[i - k];
		  idx = i;
		}
	 }
	 printf ("%i\n", idx - k + 2);

	 return EXIT_SUCCESS;
}
