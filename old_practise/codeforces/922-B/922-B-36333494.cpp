#include <bits/stdc++.h>
using namespace std;

int logic(int x, int y, int z){
	if (x + y > z && x + z > y && z + y > x) return 1;
	else return -1;
}
int main(int argc, char *argv[]){
	int start_s=clock();
	long int n, counter = 0;; cin >> n;

	for (int i = 1; i <= n-2; i++) for (int j = i; j <= n-1; j++) 
		if (int(i^j) >= j && int(i^j) <=n) 
			if (logic(i, j, i^j) == 1) counter++;

	cout << counter << endl;

	int stop_s=clock();
//	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;
}