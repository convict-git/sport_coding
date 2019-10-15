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
int n, m;
set <int> s;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int k;
	fr(i, 2, ceil(sqrt(50))){
		k = 0;
		while(i*i + i*k <= 50)
			s.insert(i*(i+(k++)));
	}
	cin >> n >> m;
	k = 0;
	while(m - k > n){
		if (k == 0 && find(all(s), m-k) != s.end())
		{cout << "NO" << "\n"; return 0;}
		else if (k!= 0 && find(all(s), m-k) == s.end())
		{cout << "NO" << "\n"; return 0;}
		k++;
	}
	R("YES"); 
		//Beware no shit stuff here!
}