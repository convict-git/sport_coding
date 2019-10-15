/* author: Priyanshu Shrivastav, from IIT Palakkad *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define se second
#define fi first
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define SQR(x) ((x)*(x))
#define MOD(x) ((x)%_mod)
#define INF (_mod-7)
#define EPS ((ld)1e-9)
#define MAXN ((int)1e5+10)

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

const ui _mod = (ui)1e9 + 7;

bool cycle = false;
int n, m;
char A[51][51];
int vis[51][51] = {0}; //2d array for visited node
int dx[] = {1, -1 , 0, 0};
int dy[] = {0,  0, -1, 1};

void dfs (int i, int j, int i0, int j0) {
  if (i0 == -1 && j0 == -1) ;
  else if (i < 0 || j < 0 || i >= n || j >= m || cycle || A[i][j] != A[i0][j0]) return;
  if (vis[i][j]) {
	 cycle = true;
	 return;
  }
  vis [i][j] = 1;

  for (int ii = 0; ii < 4; ii++) {
	 if (i + dx[ii] == i0 && j + dy[ii] == j0)
		continue;
	 dfs (i + dx[ii], j + dy[ii], i, j);
  }
}

int main() {
	 ios_base::sync_with_stdio(false);
	 cin.tie (NULL); cout.precision (10); cout << fixed;

	 cin >> n >> m;
	 for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		  cin >> A[i][j];

	 for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		  if (!vis[i][j])
			 dfs (i, j, -1, -1);

	 if (cycle) cout << "Yes\n";
	 else cout << "No\n";

	 return 0;
}
