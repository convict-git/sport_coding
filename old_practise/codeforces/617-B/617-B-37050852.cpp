/*author* Priyanshu Shrivastav
 *_ __ ___  _ __ ___ ___  _ ____   ___  ___| |_ 
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_ 
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
 * Now, God only knows*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first
#define fr(x,y,z) for(auto x=y;x!=z;++x)
#define fo(n) for(int i=0;i<n;i++)
#define fm(m,n) fr(i,0,m) fr(j,0,n)
#define all(v) v.begin(),v.end()
#define vit vector<int>::iterator it
#define sit set<int>::iterator it
#define R(x); {cout << x << "\n"; return 0;}
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

ll n;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll i, m = 1, f=0, c = 0;
	cin >> n;
	while(n--){
		cin >> i; 
		i == 1 ?  (f == 1 ?  m*=(c+1) : m), f = 1, c = 0 : c+=1;
	}
	if (f == 0) cout << "0\n";
	else cout << m << '\n'; 
		//Beware no shit stuff here!
}