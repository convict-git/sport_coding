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

int main(int argc, char *argv[]){
	//printf("Starts working!\n");//Comment it after debugging
	int n, me = 1, f = 1000000, ai, time1 = 0, time2 = 0;
	cin >> n;
	vector <pair <int,int> > v;
	for (int i = 0; i < n; i++){
		cin >> ai;
		time1 = max(((ai - me) > (f - ai) ? 0 : ai - me), time1);
		time2 = max(((ai - me) > (f - ai) ? f - ai : 0) ,time2);
	}
	cout << max(time1,time2);
}