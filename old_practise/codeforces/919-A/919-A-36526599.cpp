#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
	int n, m, a, b; cin >> n >> m;
	double f=(double) 1e5;
	for (int i = 0; i < n; i++){ cin >> a >> b;
		if ((double) a/b <= f) f = (double) a/b;
	}
	printf("%.9f\n", f*m);
}