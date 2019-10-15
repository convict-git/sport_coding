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
#include 		  <cstdint>
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
#define PREC     cin.tie (NULL); cout.precision (10); cout << fixed

using namespace std;
int warnscanf_shit;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7;
const int MAXN = 1e6 + 10;
int N, x, jtN[MAXN];
ll fq[MAXN], Z, dp[MAXN], ways = 0;;

void solve () {
  for (int i = 0; i < N; ++i) {
	 if (i) jtN[i] = (Z - fq[i - 1] == Z/3);
	 else jtN[i] = 0;
  }
  dp[N - 1] = 1LL*jtN[N - 1];
  for (int i = N - 2; i >= 0; --i) {
	 dp[i] = 1LL*jtN[i] + dp[i + 1];
  } //including i how many have sm Z/3 from i to N - 1

  for (int i = 0; i < N - 1; ++i) {
	 if (fq[i] != Z/3) continue;
	 else {
		ways += dp[i + 2]; //atleast one element in each set so start from i + 2
	 }
  }
  cout << ways << '\n';
}

int main() {
	 //IOS; PREC;
	 scanf ("%i", &N);
	 for (int i = 0; i < N; ++i) {
		scanf ("%lld", fq + i);
		if (i) fq[i] += fq[i - 1];
	 }
	 Z = fq[N - 1];
	 if (Z%3 != 0) return 0*printf ("0\n");
	 solve();
	 return EXIT_SUCCESS;
}

