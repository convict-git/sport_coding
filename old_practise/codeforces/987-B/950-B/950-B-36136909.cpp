/*
	 ***************************************************************
	 ||   Author                         {Priyanshu Shrivastav}	  || 
	 ||   email  {official[dot]mr[dot]convict[at]gmail[dot]com}   || 
	 ***************************************************************
	**_ __ ___    _ __    ___    ___    _ __   __   __ (_)   ___  | |_ 
	 | '_ ` _ \  | '__|  / __|  / _ \  | '_ \  \ \ / / | |  / __| | __|
	 | | | | | | | |    | (__  | (_) | | | | |  \ V /  | | | (__  | |_ 
	 |_| |_| |_| |_|     \___|  \___/  |_| |_|   \_/   |_|  \___|  \__|
	 ***************************************************************
	 */

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
	int start_s=clock();
	int n, m, counter = 0, x = 0, y = 0, sumv1 = 0, sumv2 = 0;
	cin >> n >> m;
	vector <int> v1(n), v2(m);

	for (int i = 0; i < n; i++) cin >> v1.at(i);
	for (int j = 0; j < m; j++) cin >> v2.at(j);

	sumv1 = v1.at(0); sumv2 = v2.at(0);
	while (x < n && y < m){
		if (sumv1 == sumv2){
			counter++; 
			if (x < n-1 && y < m-1){
				sumv1 = v1.at(++x); sumv2 = v2.at(++y);
			} else break;
		}
		else if (sumv1 < sumv2) sumv1+=v1.at(++x);
		else sumv2+=v2.at(++y); 
	} cout << counter << endl;

	int stop_s=clock();
//	cout << "time taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;
}