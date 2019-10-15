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

int main(){
	int x, y;
	cin >> x >> y;
	if (y == 0) cout << "No" << endl;
	else if (x == 1 && y == 0 || x + 1 < y) cout << "No" << endl;
	else if (y == 1 && x != 0) cout << "No" << endl;
	else if ((x - y + 1)%2 == 0) cout << "Yes" << endl;
	else cout << "No" << endl;
}