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
#define sqr(x) (x)*(x)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

template <typename T> T gcd(T a, T b){if(b > a) swap(a, b); return b ? gcd <T> (b,a%b):a;}
template <typename T> T lcm(T a,T b){return(a*b)/gcd<T>(a,b);}
template <typename T> T son(T n){int k=1; while(n/(T)pow(10,k) != 0) k+=1; return k;}

const ui N = 1000000007;

typedef struct p {
	double x, y;
} p;

double dist (p p1, p p2){
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif
	int r, d, n, r_i, c = 0;
	cin >> r >> d >> n;
	p p1, p2;
	p1 = {0, 0};
	for (int i = 0; i < n; i++) {
		cin >> p2.x >> p2.y >> r_i;
		double di = dist (p1, p2);
		if (di - r_i >= r - d) if (di + r_i <= r) c++;
	}
	cout << c << '\n';

#ifdef CONVICTION
	cout << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif
	return 0;
}