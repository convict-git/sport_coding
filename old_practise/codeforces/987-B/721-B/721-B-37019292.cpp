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

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;
int n, k, as, p = 0, c = 0, mn = 0, mx = 0;
string a;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int A[100]; fill_n(A, 100 ,0);
	cin >> n >> k;
	if (n==1) {cout << 1 << " " << 1 << "\n"; return 0;}

	fo(n){
		string s; cin >> s;
		A[s.size()-1]+=1;
	}
	cin >> a; as = a.size();
	fo(as-1) p+=A[i];

	mn+= (p/k)*5 + p;
	c+= p%k + A[as-1] - 1;
	mx += mn + (c/k)*5 + c - p%k+ 1;
	mn+=1;
	cout << mn << " " << mx << "\n"; 
	//Beware no shit stuff here!
}