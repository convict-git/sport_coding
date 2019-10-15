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
	string st; cin >> st;
	char pos = 'a'; pos--;
	if (st.size() < 26) { cout << -1 << endl; return 0;}
	for (size_t i = 0; i < st.size(); i++){
		if (pos=='z'){cout << st << endl; return 0;}
		if (st[i] <= (pos+1)){
			if (st[i] < pos+1) st[i]=++pos;
			pos = st[i];
		}
	}if (pos!='z')cout << -1 << endl;
	else cout << st << endl;
	int stop_s=clock();
	//cout << "time taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;
}