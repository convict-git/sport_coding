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
//const int MAXN = 1e5 + 10; string strBin;
set <int> s;
int m;

bool solver (vector <int> &smaller, int &smLarger, int &smSmaller, int &prv) {
	int findIt = smLarger - smSmaller;
	auto it = s.upper_bound (findIt);
	if (it != s.end()) {
		if (*it == prv) ++it;
		if (it == s.end()) return false;
		prv = *it;
		smSmaller += *it;
		smaller.push_back (*it);
		return true;
	}
	else return false;
}

void solve() { // I kind of know it still wont' work
	bool ok = false;
	vector <int> lft, rgt;
	for (auto itSet = s.begin(); itSet != s.end(); ++itSet) {
		int sml = 0, smr = 0, prv = 0;
		prv = *itSet, sml += *itSet;
		lft.push_back (*itSet);

		ok = (s.size() != 0 && m == 1);//corner case

		for (int i = 1; i < m; ++i) {
			if (i%2 == 0) ok = solver (lft, smr, sml, prv);
			else ok = solver (rgt, sml, smr, prv);
			if (!ok) {
				lft.clear(), rgt.clear();
				assert (lft.size() == 0 && rgt.size() == 0);
				break;
			}
		}
		if (!ok) continue;
		assert ((int)lft.size() == (m + (m&1))/2);
		assert ((int)rgt.size() == m/2);
		vector <int> ::iterator itLeft = lft.begin(), itRight = rgt.begin();
		cout << "YES\n";
		for (int i = 0; i < m; ++i) {
			if (i%2 == 0) cout << (int)*itLeft << ' ', ++itLeft;
			else cout << (int)*itRight << ' ', ++itRight;
		}
		cout << '\n';
		return;
	}
	if (!ok) cout << "NO\n";
}

int main() {
	IOS; PREC;
	string strBin;
	getline (cin, strBin);
	assert (strBin.size() == 10);
	cin >> m;
	for (int i = 0; i < (int)strBin.size(); ++i) {
		if (strBin[i] == '1') s.insert (i + 1);
	}
	solve();
	return EXIT_SUCCESS;
}

