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
#define rall(v) (v).rbegin(),(v).rend()
#define sqr(x) ((x)*(x))
#define mod(x) ((x)%N)
#define INF 1000000000
#define bug cerr << "bug!\n"

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

const ui N = 1000000007;

int main(int argc, char *argv[]){
#ifdef CONVICTION
	freopen("in", "r", stdin);
	int start_s=clock();
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.precision(10);
	cout << fixed;

	/*solution starts here...*/
	int p, s;
	cin >> p >> s;
	vector <vii> v(p);
	vii n(p);

	for (int i = 0; i < p; i++) {
		n[i] = {0, i+1};
		v[i].resize (s);

		for (int k = 0 ; k < s; k++)
			cin >> v[i][k].fi;
		for (int k = 0; k < s; k++)
			cin >> v[i][k].se;

		sort (all(v[i]));
		for (int k = 1; k < s; k++)
			v[i][k].se < v[i][k-1].se ? n[i].fi++ : n[i].fi;
	}

	sort (all (n));
	for (int i = 0; i < p; i++)
		cout << n[i].se << '\n';

#ifdef CONVICTION
	cerr << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif

//Beware no shit stuff here!
	return 0;
}

