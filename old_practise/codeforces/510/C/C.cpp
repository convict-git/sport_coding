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
int n, tme = 0;
vector <string> vs;
vector < vector <int> > edge;
inline int toInt (char c) { return (int) (c - 'a'); }
bool ok = false;
vector < pair <int, int> > startTime, endTime;
vector <int> vis;

void dfs (int u) {
	vis[u] = 1;
	startTime[u] = {tme, u};
	++tme;

	for (auto v : edge[u]) {
		if (vis[v] == 0) dfs (v);
	}
	endTime[u] = {tme, u};
	++tme;
}

bool findCycle () {
	for (int u = 0; u < 26; ++u) {
		for (auto v : edge[u]) { //if reveals backedge
			if (startTime[u].first > startTime[v].first &&
					endTime[u].first < endTime[v].first) {
				return true;
			}

		}
	}
	return false;
}

int main() {
	IOS; PREC;
	cin >> n; cin.ignore();

	for(int i = 0; i < n; ++i) {
		string s;
		getline (cin, s);
		vs.push_back (s);
	}
	assert ((int) vs.size() == n);

	edge.resize(26); //directed edges please take care
	startTime.resize(26), endTime.resize(26), vis.resize(26);
	for (auto &ver : vis) ver = 0;

	for (int i = 0; i < n - 1; ++i) {
		bool found = false;
		int szMin = min ((int) vs[i].size(), (int) vs[i + 1].size());
		for (int j = 0; j < szMin; ++j) {
			if (vs[i][j] != vs[i + 1][j]) {
				edge[toInt (vs[i][j])].push_back (toInt (vs[i + 1][j]));
				found = true;
				break;
			}
		}
		if (!found) {
			if (vs[i].size () > vs[i + 1].size()) { //Most hacks were here
				ok = false;
				cout << "Impossible\n";
				return EXIT_SUCCESS;
			}
		}
	}

	for (int u = 25; u >= 0; --u)
		if (vis[u] == 0) dfs (u);

	ok = findCycle ();
	if (ok) {
		cout << "Impossible\n";
	} else {
		sort (all (endTime));
		reverse (all (endTime));
		for (auto it : endTime) {
			cout << (char) (it.second + 'a');
		} cout << '\n';
	}

	return EXIT_SUCCESS;
}


