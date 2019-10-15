#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, ai, c=0; cin >> n;
	int b[n]= {0};
	vector <int> p;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			cin >> ai;
			if (ai == 0 || ai == 2) b[i]+=1;
		} 
	}
	for (int i = 0; i < n; i++)
		if (b[i] == n-1) c+=1, p.push_back(i+1);

	cout << c << endl; 
	for (size_t i = 0; i < p.size(); i++) cout << p.at(i) << " ";
}
//I can write this way too -_-