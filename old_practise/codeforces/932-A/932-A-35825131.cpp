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

int isPal(string st){
	for (int i = 0; i < ceil(st.size()/2); i++)
		if (st[i] != st[st.size() - 1 - i]) return 1;
	return 0;
}
string makePal(string st){
	vector <char> c;
	while(1){
		c.push_back(st[st.size()-1]);
		st.erase(st.end()-1,st.end());
		if (isPal(st) == 0){
			for (int i = c.size() -1; i >= 0; i--){
				if(st.size() <= 1e4){
					st.insert(0,1,c.at(i));
					st.insert(st.end(),1,c.at(i));
				}else return "Error";
			}return st;
		}
	}
}
int main(int argc, char *argv[]){
	string inp;
	cin >> inp;
	if (isPal(inp) == 0) cout << inp << endl;
	else cout << makePal(inp) << endl;
	return 0;
}