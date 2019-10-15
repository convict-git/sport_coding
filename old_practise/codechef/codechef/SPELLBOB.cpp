/*author* Priyanshu Shrivastav
*from*(IIT Palakkad)
 *_ __ ___  _ ______ ___  _ ____   ___  ___| |_
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
 * Now, only God knows*/

#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define se second
#define fi first
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sqr(x) ((x)*(x))
#define mod(x) ((x)%N)
#define INF 1000000000

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

const ui N = 1000000007;

int main() {
#ifdef CONVICTION
	FILE* p = freopen("in", "r", stdin);
	if (!p) return 26;
	int start_s=clock();
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.precision(10);
	cout << fixed;

	/*solution starts here...*/
	int t, f;
	string match[3] = {"bob", "obb", "bbo"};
	cin >> t;
	while (t--) {
		string s[2], r = "cat";
		f = 0;
		for (int i = 0; i < 2; cin >> s[i++]);


		int n, i;
		set <int> a;
		cin >> n;
		while (n--) cin >> i, a.insert (i);
		cout << a.size() << '\n';

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++) {
					r[0] = (char)s[i][0];
					r[1] = (char)s[j][1];
					r[2] = (char)s[k][2];
					for (int l = 0; l < 3; l++)
						if (!r.compare (match[l])) {
							l = 4, k = 3, j = 3, i = 3, f = 1;
						}
				}
		cout << (f == 1 ? "yes\n" : "no\n");
	}

#ifdef CONVICTION
	cout << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif

//Beware no shit stuff here!
	return 0;
}

