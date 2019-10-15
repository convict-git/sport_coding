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
#include         <cassert>
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
const int MAXN = 3e2 + 10;
int vis[MAXN][MAXN] = {0};
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int n, m, k, visc = 0, curx, cury;
void solve(int ktemp) {
  if (ktemp == 0) return;
  vis[curx][cury] = 1, ++visc;
  printf ("%i %i ", cury, curx);
  for (int i = 0; i < 4; ++i) {
	 if (curx + dx[i] > n || curx + dx[i] < 1) continue;
	 if (cury + dy[i] > m || cury + dy[i] < 1) continue;
	 if (vis[curx + dx[i]][cury + dy[i]] == 1) continue;
	 else {
		curx += dx[i], cury += dy[i];
		solve(ktemp - 1);
		return;
	 }
  }
}

int main() {
  //IOS; PREC;
  scanf ("%i%i%i", &m, &n, &k);
  assert (2*k  <= n*m && k >= 1);
  int c = 0;

  visc = 0, curx = cury = 1;
  int t = n*m;
  int rem = t%k;
  if (rem != 0) {
	 t -= (rem + t/k);
  }
  while (visc != t) {
	 printf ("%i ", n*m/k), ++c;
	 solve(n*m/k);
	 printf ("\n");
  }
  if (rem != 0) {
	 printf ("%i ", rem + n*m/k), ++c;
	 solve (rem + n*m/k);
	 printf ("\n");
  }
  assert (c == k);

  return EXIT_SUCCESS;
}

