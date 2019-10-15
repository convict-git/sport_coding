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

int islucky(int i){
	if ((i - (i/10)*10) - 7 == 0) return 1;
	else return 0;
}

int main(int argc, char *argv[]){
	int start_s=clock(); 
	int x, hh, mm, y = 0;
	pair <int,int> timex;
	cin >> x >> hh >> mm;

	while(islucky(hh) == 0 && islucky(mm) == 0){
		mm-=x;
		if (mm < 0){ mm+=60; hh--;}
		if (hh < 0) hh = 23;
		y++;
	}
	cout << y << endl; 
		int stop_s=clock();
		//cout << "time taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

	return 0;
}