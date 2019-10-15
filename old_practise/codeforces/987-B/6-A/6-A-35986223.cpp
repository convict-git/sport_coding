/*
	 ***************************************************************
	 ||   Author                         {Priyanshu Shrivastav}	  || 
	 ||   handle																	 {mr.convict}	  || 
	 ||   github																  {convict-git}	  || 
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
int logic(int x, int y, int z){
	int tri = 0, seg = 0;
	if (x + y > z && x + z > y && z + y > x) tri = 1;
	else if (x+y==z || x+z==y || z+y==x) seg = 1;

	if (tri == 1) return 1;
	else if (seg == 1) return 0;
	else return -1;
}
int main(int argc, char *argv[]){
	int start_s=clock();
	int a[4], seg = 0;
	for (int i = 0; i < 4; i++) cin >> a[i];
	for (int i = 0; i < 2; i++){
		for (int j = i+1; j < 3; j++){
			for (int k = j+1; k < 4; k++){
				if (logic(a[i], a[j], a[k]) == 1){
					cout << "TRIANGLE" << endl; return 0;
				} else if (logic(a[i], a[j], a[k]) == 0) seg = 1;
			}
		}
	}
	if (seg == 1) cout << "SEGMENT" << endl;
	else cout << "IMPOSSIBLE" << endl; 
	int stop_s=clock();
	//cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;
}