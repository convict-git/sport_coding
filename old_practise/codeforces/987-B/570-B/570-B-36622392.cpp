#include <bits/stdc++.h>
#define er(x, y) cout<<x<<" "<<y
using namespace std;
int main(int argc, char *argv[]){
	int n, m; cin >> n >> m; assert(n>=m);
	if (n!=1) m<=n/2 ? er(m+1,endl): er(m-1,endl) ;
	else er(1,endl);
}