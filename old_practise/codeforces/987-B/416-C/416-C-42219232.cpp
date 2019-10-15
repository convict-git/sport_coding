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
using namespace std;
using namespace __gnu_pbds;

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

struct req {
	 int per;
	 int cost;
	 int index;
};

struct ans {
	 int order;
	 int table;
};
struct table {
	 int index;
	 int cap;
	 int vis;
};

bool comp (req p, req q) { return p.cost > q.cost; }
bool comp2 (table p, table q) {return p.cap < q.cap; }

void solve (req* A, int n, table* r, int k) {
	 int m = 0, s = 0;
	 vector <ans> Ans;
	 for (int i = 0; i < n; i++) {
		  for (int j = 0; j < k; j++) {
				if (!r[j].vis && A[i].per <= r[j].cap) {
					 s += A[i].cost;
					 m += 1;
					 r[j].vis = 1;
					 Ans.pb ({A[i].index, r[j].index});
					 break;
				}
		  }
	 }
	 cout << m << ' ' << s << '\n';
	 for (auto &it : Ans)
		 cout << it.order << ' ' << it.table << '\n';
}

int main() {
#ifdef CONVICTION
	 if(!freopen ("in", "r", stdin)) return 26;
#endif
	 ios_base::sync_with_stdio(false);
	 cin.tie (NULL); cout.precision (10); cout << fixed;

	 /*solution starts here...*/
	 int n, k, j;
	 cin >> n;
	 req A[n];
	 for (int i = 0; i < n; i++) {
		  int c, p;
		  cin >> c >> p;
		  A[i] = {c, p, i + 1};
	 }
	 cin >> k;
	 table r[k];

	 for (int i = 0; i < k; i++)
		  cin >> j, r[i] = {i + 1, j, 0};

	 sort (r, r + k, comp2);
	 sort (A, A + n, comp);

	 solve (A, n, r, k);

	 return 0;
}