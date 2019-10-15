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

	int n, k;
	string s;
	cin >> n >> k >> s;

	while(k!=0){
		for (size_t i = 0; i < s.size()-1; i++)
			if (s[i] == 'B' && s[i+1] == 'G')
			{s[i] = 'G'; s[i+1] = 'B'; i++;}
		k--;
	}
	cout << s << endl;
	int stop_s=clock();
	//cout << "time taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;
}