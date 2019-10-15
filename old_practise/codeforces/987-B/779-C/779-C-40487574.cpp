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
#define forn(i, j, k) for (int i = j; i < (int) k; i++)
#define forN(i, j, k) for (int i = (int) k-1; i >= j; i--)
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define err(x) cerr << #x << " = " << x << ' '
#define mod(x) ((x)%N)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

template <typename T> T powr(T a, T b) {T k = 0; while (a%b == 0) a/=b, k+=1; return k;}
template <typename T> T gcd(T a, T b) {if(b > a) swap(a, b); return b ? gcd <T> (b,a%b):a;}
template <typename T> T lcm(T a,T b) {return(a*b)/gcd<T>(a,b);}

const ui N = 1000000007;

bool comp (pii p, pii q) {
	return p.fi - p.se < q.fi - q.se;
}

int main(int argc, char *argv[]){
#ifdef CONVICTION
	freopen("in", "r", stdin);
	int start_s=clock();
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	/*solution goes here...*/
	int n, k, s;
	cin >> n >> k;
	pii A[n];
	forn (i, 0, n) cin >> A[i].fi;
	forn (i, 0, n) cin >> A[i].se;
	sort (A, A+n, comp);
	s = 0;

	forn (i, 0, k) s+=A[i].fi;
	int i = k;
	while (i < n) {
		if (A[i].fi < A[i].se)
			s+=A[i++].fi;
		else 
			while (i < n)
				s+=A[i++].se;
	}

	cout << s << '\n';

#ifdef CONVICTION
	cout << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif

	//Beware no shit stuff here!
	return 0;
}