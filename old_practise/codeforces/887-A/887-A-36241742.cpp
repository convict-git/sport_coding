/* ***************************************************************
	 ||   Author                         {Priyanshu Shrivastav}	  || 																  {convict-git}	  || 
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
	int start_s= clock();
	char c;
	int counter = 0, flag = 0;
	while((c=getchar()) && c!=EOF){
		if (c == '1') flag = 1;
		if (c == '0' && flag == 1) counter+=1;
		if (counter >= 6){cout << "yes" << endl; return 0;}
	}
	cout << "no" << endl;
	int stop_s = clock();
	//cout << "time taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;
}