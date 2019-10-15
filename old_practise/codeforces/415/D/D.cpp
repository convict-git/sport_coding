#include         <iostream>
#include         <algorithm>
#include         <cstdlib>
#include         <functional>
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
const int maxn = 1e5 + 10;
const int _mod = 1e9 + 7;
const int mxn = 2010;
int n, k;
int dp[mxn][mxn], sm;

int main() {
	 //IOS; PREC;
	 while ((scanf("%i%i", &n, &k)) == 2) {
		  for (int i = 1; i < mxn; ++i)
				for (int j = 1; j < mxn; ++j) dp[i][j] = 0;
		  for (int j = 1; j < mxn; ++j)
				dp[1][j] = 1;

		  for (int i = 1; i < k; ++i) {
				for (int j = 1; j <= n; ++j) {
					 for (int x = 1; x * j <= n; ++x) {
						  dp[i + 1][x * j] += dp[i][j];
						  dp[i + 1][x * j] %= _mod;
					 }
				}
		  } sm = 0;
		  for (int it = 1; it <= n; ++it) {
				sm += dp[k][it];
				sm %= _mod;
		  }
		  printf ("%i\n", sm);
	 }
	 return EXIT_SUCCESS;

