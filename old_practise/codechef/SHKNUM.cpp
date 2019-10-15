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
#define bug cerr << "here!\n"

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

const ui N = 1000000007;

pair <ull*, ull> table () {
	ull k = 0, j = INF, m;
	while (j)
		j/=2, k++;
	k++;
	m = (k*(k-1))/2;
	ull *A = new ull [k],
		*B = new ull [m];

	A[0] = 1;
	for (int i = 1; i < (int)k; i++)
		A[i] = 2*A[i-1];

	int l = 0;
	for (int i = 0; i < (int)k-1; i++)
		for (int j = i+1; j < (int)k; j++)
			B[l++] = A[i] + A[j];
	sort (B, B+m);
	return {B, m};
}

int main(int argc, char *argv[]){
#ifdef CONVICTION
	FILE* p = freopen("in", "r", stdin);
	int start_s=clock();
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.precision(10);
	cout << fixed;

	ull* tb = table().fi;
	ull m = table().se;
	//cout << m << '\n';
	//for (int i = 0; i < (int)m ; i++)
		//cout << tb[i] << '\n';

	/*solution starts here...*/
	int t;
	cin >> t;
	while (t--) {
		ull n;
		cin >> n;
		for (int i = 0; i < (int)m; i++) {
			if (n >= tb[i] && n < tb[i+1]) {
				cout << min (n- tb[i], tb[i+1] - n) << '\n';
				break;
			}
			else if (n == tb[i+1]) {
				cout << 0 << '\n';
				break;
			}
			else if (n < tb[i]) {
				cout << tb[i] - n << '\n';
				break;
			}
		}
	}


#ifdef CONVICTION
	cout << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif

//Beware no shit stuff here!
	return 0;
}

