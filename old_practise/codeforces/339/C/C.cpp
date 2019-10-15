#pragma GCC      optimize ("Ofast")
#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <vector>
#include         <map>
#include         <set>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define bug(s,x) fprintf(stderr,"[%s %s : %i]\n",s,#x,x),fflush(stderr)
#define bg(x)    bug ("bug : ", x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed

using namespace std;
int warnscanf_shit;
typedef long long ll;
typedef unsigned long long ull;
const int MOD = 1e9 + 7;
//const int MAXN = 1e5 + 10;

vector <int> Weights, ans;
string s;
int m;
bool dfs (int curBal, int prvWeight, int turns) {
	if (turns > m) return true;
	bool ok = false;
	for (auto w : Weights) {
		if (curBal >= 0 && prvWeight != w && curBal - w < 0) {
			ok = dfs (curBal - w, w, turns + 1);
		}
		else if (curBal < 0 && prvWeight != w && curBal + w > 0) {
			ok = dfs (curBal + w, w, turns + 1);
		}
		if (ok) {
			ans.push_back (w);
			return true;
		}
	}
	return false;
}

int main() {
	//IOS; PREC;

	getline (cin, s);
	assert (s.size() == 10);
	cin >> m;

	for (int i = 0; i < (int)s.size(); ++i) {
		if (s[i] == '1') Weights.push_back (i + 1);
	}
	reverse (all (Weights));
	bool ok = dfs (0, 0, 1);
	if (ok) {
		cout << "YES\n";
		reverse (all (ans));
		for (auto it : ans) cout << it << ' ';
	}
	else cout << "NO";
	cout << '\n';
	return EXIT_SUCCESS;

}


