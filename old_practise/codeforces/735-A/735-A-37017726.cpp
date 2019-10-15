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
#define R(x,y); {er(x,y); return 0;}

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;
string s;
char c;
int n, k, f = 0;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;
	while(n--){
		cin >> c;
		if (c=='G' || c=='T') f+=1;
		f <= 2 && f!= 0 ? s+=c : s;
		if (f >=2) break;
	}

	if (s[0] != 'G') reverse(all(s));

	for (int i = 0 ; i < s.size(); i+=k){
		if (s[i] == '#') break;
		if (s[i] == 'T') {cout << "YES\n"; return 0;}
	} cout << "NO\n";


	//Beware no shit stuff here!
}