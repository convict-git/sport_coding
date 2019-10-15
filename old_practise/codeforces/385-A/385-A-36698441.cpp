/*author* Priyanshu Shrivastav
 *_ __ ___  _ __ ___ ___  _ ____   ___  ___| |_ 
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_ 
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
 * Now, God only knows*/

#include <bits/stdc++.h>
#define ll long long
#define fo(n) for(ll i=0;i<n;i++)
#define e(x) cout<<x<<" "
using namespace std;

int main(int argc, char *argv[]){
	int n, c, a, b, p = 0;
	cin >> n >> c >> a;
	fo(n-1) cin >> b, a>p+b+c ? p = a-b-c : p, a = b; e(p)<<endl;
}