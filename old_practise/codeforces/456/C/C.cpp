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
const int MAXN = 1e5 + 10;
int N, fq[MAXN + 1] = {0};
ll dp[MAXN + 1][2];

void solve() {
  dp[1][0] = 1ll*fq[1]; dp[1][1] = 0;
  for (int i = 2; i <= MAXN; ++i) {
	 dp[i][0] = 1ll*fq[i]*i + dp[i - 1][1];
	 dp[i][1] = max (dp[i - 1][0], dp[i - 1][1]);
  }
  cout << max (dp[MAXN][0], dp[MAXN][1]) << '\n';
}

int main() {
	 IOS; PREC;
	 cin >> N;
	 int tmp;
	 for (int i = 1; i <= N; ++i) {
		cin >> tmp;
		++fq[tmp];
	 }
	 solve();

	 return EXIT_SUCCESS;
}

