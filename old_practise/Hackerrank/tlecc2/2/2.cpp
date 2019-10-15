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
const int MAXN = 1e6 + 10;

int N, Ar[MAXN];
ll dp[MAXN][3];

int main() {
  IOS; PREC;
  cin >> N;
  for (int i = 0; i < N; ++i) {
	 cin >> Ar[i];
  }

  dp[0][0] = Ar[0];
  dp[0][1] = dp[0][2] = -1;
  for (int i = 1; i < N; ++i) {
	 bool ok = false;
	 for (int j = 0; j < 3; ++j) {
		if (Ar[i] >= dp[i - 1][j]) {
		  if (j == 0) {
			 dp[i][2] = dp[i - 1][1];
			 dp[i][1] = dp[i - 1][0];
			 dp[i][0] = Ar[i];
		  }
		  else if (j == 1) {
			 dp[i][2] = dp[i - 1][1];
			 dp[i][1] = Ar[i];
			 dp[i][0] = dp[i - 1][0];
		  }
		  else if (j == 2) {
			 dp[i][2] = Ar[i];
			 dp[i][1] = dp[i - 1][1];
			 dp[i][0] = dp[i - 1][0];
		  }
		  ok = true;
		  break;
		}
	 }
	 if (!ok) {
		for (int j = 0; j < 3; ++j) {
		  dp[i][j] = dp[i - 1][j];
		}
	 }
  }

  for (int i = 0; i < N; ++i) {
	 if (dp[i][2] == -1) cout << -1 << '\n';
	 else cout << 1ll*dp[i][0]*dp[i][1]*dp[i][2] << '\n';
  }

  return EXIT_SUCCESS;
}


