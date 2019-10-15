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
//const int MAXN = 1e5 + 10;

int n, p;
int idx, defSum = 0, caseSum = 0, l = -1, r = -1;
string s;
inline int changeChar (char c1, char c2) {
  int diff = abs (c1 - c2);
  return (diff <= 13 ? diff : 26 - diff);
}

void solve () { //why travelling extra
  auto solver = [&] (int M)->void {
	 for (int i = 1; i <= M; ++i) {
		idx = i - 1;
		if (s[idx] != s[n - 1 - idx]) {
		  l == -1 ? l = r = i : r = i;
		}
		defSum += changeChar (s[idx], s[n - 1 - idx]);
	 }
	 if (defSum != 0) {
		caseSum = r - l;
		if (p > M) {
		  l = n + 1 - l;
		  r = n + 1 - r;
		}
		caseSum += min (abs(l - p), abs(p - r));
	 }
  };
  if (n&1) solver ((n + 1)>>1);
  else solver(n>>1);
  cout << defSum + caseSum << '\n';
}

int main() {
  IOS; PREC;
  cin >> n >> p;
  cin >> s;
  solve();
  return EXIT_SUCCESS;
}

