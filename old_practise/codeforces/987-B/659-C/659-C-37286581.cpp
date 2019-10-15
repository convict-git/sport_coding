/*
Fri Apr 13 23:46:54 IST 2018
*author* Priyanshu Shrivastav 
 * *from*(IIT Palakkad)
 *_ __ ___  _ __ ___ ___  _ ____   ___  ___| |_ 
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
#define fr(x,y,z) for(auto x=y;x!=z;++x)
#define fo(n) for(int i=0;i<(int)n;i++)
#define forn(i, n) for (int i=0;i<(int)n;i++)
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define R(x); {cout << (x) << "\n"; return 0;}
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

template <typename T> T gcd(T a, T b){T t,x,y; x = max(a,b); y=min(a,b); while(y!=0){t=x; x=y; y=t%y;} return x;}
template <typename T> T lcm(T a,T b){return(a*b)/gcd<T>(a,b);}
template <typename T> T son(T n){int k=1; while(n/(T)pow(10,k) != 0) k+=1; return k;} 

ll n, m, *a;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif

ll x, k;
vector <int> v;

cin >> n >> m;
a = (ll*) malloc(sizeof(ll)*n);
fo(n) cin >> a[i];

sort(a, a+n);
for (k = 1; (k*(k+1))/2 <= m; k++);
k-=1;
x = m-(k*(k+1))/2;

fo(n) if (a[i] <= k) x+=a[i];

for (ll i = 1; i <= k; i++)
	if (!binary_search(a, a+n, i)) v.pb(i); 

for (int j = k+1; x - j >= 0; j++){
	if (!binary_search(a, a+n, j)){
		x-=j;
		v.pb(j); // for answer
	} 
}

cout << v.size() << "\n";
if (v.size())
	for(auto &it:v) cout << it << " ";
cout << "\n"; 

#ifdef CONVICTION
	cerr << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif
	return 0;
	//Beware no shit stuff here!
}