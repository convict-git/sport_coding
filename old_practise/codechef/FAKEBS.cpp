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
#define forn(i, j, k) for (int i = j; i < (int)k; i++)
#define forN(i, j, k) for (int i = k-1; i >= j; i--)
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define err(x) cerr << #x << " = " << x
#define pii pair <int, int> 
#define mod(x) ((x)%N)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
 
using namespace std;
 
template <typename T> T gcd(T a, T b){if(b > a) swap(a, b); return b ? gcd <T> (b,a%b):a;}
template <typename T> T lcm(T a,T b){return(a*b)/gcd<T>(a,b);}
template <typename T> T son(T n){int k=1; while(n/(T)pow(10,k) != 0) k+=1; return k;} 
 
const ui N = 1000000007;
bool comp(pii, pii);
int bs(int*, int*, int, int*);
int bsp(pii*, pii*, int);
int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif
	int t;
	cin >> t;
	while (t--){ 
		int n, q, *B, *C;
		pii *A;
		cin >> n >> q;
		A = (pii*) malloc(sizeof(pii)*n);
		B = (int*) malloc(sizeof(int)*n);
		C = (int*) malloc(sizeof(int)*n);
		forn(i, 0, n) cin >> A[i].fi, C[i] = B[i] = A[i].fi, A[i].se = i; 
		sort(A, A+n, comp);
		sort(B, B+n);
 
		while (q--){ 
			vector <int> vl, vh;
			int x, p, l, h, L, m, H, c, VL, VH;
			L = c = 0, H = n-1;
			cin >> x;
			p = bsp(A, A+n, x);
			l = bs(B, B+n, x, B);
			h = n-1-l;
 
			while (L <= H){ 
				m = (L+H)/2;
				if (p == m) break;
				else if (p > m){
					if (C[m] > C[p]) vl.pb(m);
					else l-=1;
					L = m+1;}
				else if (p < m){
					if (C[m] < C[p]) vh.pb(m);
					else h-=1;
					H = m-1;}
			}
			VL = vl.size(), VH = vh.size();
			if (VH >= VL){
				c+=VL, l-=VL, h-=VL;
				if (VH - VL <= h) c+=VH-VL;
				else c = -1;
			}
			else if (VL > VH){
				c+=VH, l-=VH, h-=VH;
				if (VL - VH <= l) c+=VL-VH;
				else c = -1;
			}
			cout << c << '\n';
		} 
	}
 
#ifdef CONVICTION
	cerr << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif
	//Beware no shit stuff here!
	return 0;
}

bool comp(pii p1, pii p2){return (p1.fi < p2.fi);}

int bs(int* a, int* b, int v, int* A){
	int* g = a + (b-a)/2;
	if (*g == v) return g-A;
	else if (a+1==b) return -1;
	else if (*g > v) bs(a, g, v, A);
	else if (*g < v) bs(g, b, v, A);
}
 
int bsp(pii* a, pii* b, int v){
	pii* g = a + (b-a)/2;
	if (g->fi == v) return g->se;
	else if (a+1==b) return -1;
	else if (g->fi > v) bsp(a, g, v);
	else if (g->fi < v) bsp(g, b, v);
}
 
 
