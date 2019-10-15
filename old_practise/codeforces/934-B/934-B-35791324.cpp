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
#include <string>
using namespace std;

int main(int argc, char *argv[]){
	string n;
	int k; cin >> k;
	if (k > 36){ cout << -1 << endl; return 0;}

	for (int i = 1; i <= k/2;i++) n.append("8",1);
	for (int i = 1; i <= k%2; i++) n.append("9",1);
	cout << n << endl;
	return 0;
}