/*author* Priyanshu Shrivastav
 *_ __ ___  _ __ ___ ___  _ ____   ___  ___| |_ 
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_ 
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
 * Now, only God knows*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first
#define fr(x,y,z) for(auto x=y;x!=z;++x)
#define fo(n) for(auto i=0;i<n;i++)
#define fm(m,n) fr(i,0,m) fr(j,0,n)
#define all(v) v.begin(),v.end()
#define vit vector<int>::iterator it
#define sit set<int>::iterator it
#define R(x); {cout<<x<<"\n"; return 0;}
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

ll n, d, M = 0;
vector < pair <ll ,ll> > v;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll x, y, m = 0, p = 0;
	cin >> n >> d;
	v.resize(n);

	fo(n){
		cin >> x >> y;
		v[i] = mp(x,y);
	} sort(all(v));

	fo(n){
		if (v[i].fi < v[p].fi + d){
			m+=v[i].se;
			M = max(m, M);
		}
		else m-=v[p++].se, i--;
	} 
	cout << M << "\n";
//Beware no shit stuff here!
}