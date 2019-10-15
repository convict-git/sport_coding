/*author* Priyanshu Shrivastav 
 *from*(IIT Palakkad)
 *_ __ ___  _ ______ ___  _ ____   ___  ___| |_ 
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_ 
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 wHEN i WROTE THIS, ONLY gOD AND i UNDERSTOOD WHAT i WAS DOING
 * nOW, ONLY gOD KNOWS*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first
#define pii pair <int, int>
#define vi vector <int>
#define forn(i, j, k) for (int i = j; i < (int)k; i++)
#define forN(i, j, k) for (int i = k-1; i >= j; i--)
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define err(x) cerr << #x << " = " << x << ' '
#define mod(x) ((x)%N)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

template <typename T> T powr(T a, T b) {T k = 0; while (a%b == 0) a/=b, k+=1; return k;}
template <typename T> T gcd(T a, T b){if(b > a) swap(a, b); return b ? gcd <T> (b,a%b):a;}
template <typename T> T lcm(T a,T b){return(a*b)/gcd<T>(a,b);}


const ui N = 1000000007;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifdef CONVICTION
	freopen("in", "r", stdin);
	freopen("err", "w", stderr);
	int start_s=clock();
#endif

	int n, j = 0, a[3] = {-1, -1, -1};
	cin >> n;
	int* k = new int [n];
	forn(i, 0, n)
		cin >> k[i];
	sort (k, k+n);

	forn(i, 0, n){
		if (a[j] == -1) 
			a[j] = k[i];
		else if (j != 2 && a[j] != k[i])
			a[++j] = k[i];
		else if (j == 2 && a[j] != k[i]) {
			cout << "NO\n";
			return 0;
		}
	}

	if (j == 2 && 2*a[1] != a[0] + a[2])
		cout << "NO\n";
	else cout << "YES\n";

#ifdef CONVICTION
	cerr << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif

	//Beware no shit stuff here!
	return 0;
}