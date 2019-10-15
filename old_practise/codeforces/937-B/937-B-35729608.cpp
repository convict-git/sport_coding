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
	/*
	int p, y, j, flag;
	cin >> p >> y;
	vector <int> vec;
	for (int i = p; i >=2 ; i--){
		j = ceil((float)y/i);
		while (i*j <= y && i*j > p){
			vec.push_back(i*j);
			j--;
		}
	}
	sort(vec.begin(), vec.end());
	flag = 0;
	for (unsigned int i = vec.size()-1; i >= 1; i--)
		if(vec.at(i) - vec.at(i-1) > 1){
			cout << vec.at(i) - 1 << endl;
			flag = 1;
			return 0;
		}
	if (flag!=1)
		cout << -1 << endl;
}
*/

int p, y, flag = 0, ans = 0;
cin >> p >> y;
for (int i = y; i >= p+1; i--){
	flag = 0;
	for (int j = 2; j <= ceil(sqrt(i)) && j <= p; j++){
		if (i%j == 0){
			flag = 1;
			break;
		}
	}
	if (flag==0){
		ans = i; 
		break;
	}
}
if (ans == 0) cout << -1 << endl;
else cout << ans << endl;
}