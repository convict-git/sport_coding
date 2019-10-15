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

template <typename T> T gcd(T a, T b){if(b > a) swap(a, b); return b ? gcd <T> (b,a%b):a;}
template <typename T> T lcm(T a,T b){return(a*b)/gcd<T>(a,b);}
template <typename T> T son(T n){int k=1; while(n/(T)pow(10,k) != 0) k+=1; return k;} 

const ui N = 1000000007;

ll bin(ll *a, ll *b, ll v, ll* A){
	ll* g = a + (b-a)/2;
	if (*g == v) return g-A;
	else if (*g > v) return bin(a, g, v, A);
	else if (*g < v && *(g+1) > v) return g-A+1;
	else return bin(g, b, v, A);
}

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif
	int n, m;
	ll *A, c;
	cin >> n >> m;
	A = (ll*) malloc(sizeof(ll)*(n+2));
	A[0] = 0, A[n+1] = LLONG_MAX;
	forn(i, 1, n+1) cin >> c, A[i] = A[i-1]+c;
	forn(i, 0, m){
		cin >> c;
		ll p, q;
		p = bin(A, A+n+1, c, A);
		q = (A[p] == c ? A[p] - A[p-1] : c - A[p-1]);
		cout << p << ' ' << q << '\n';
	}

#ifdef CONVICTION
	cerr << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif
	//Beware no shit stuff here!
	return 0;
}