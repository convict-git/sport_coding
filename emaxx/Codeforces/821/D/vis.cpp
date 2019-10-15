#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;


int n, m, k, u, v;
set <pii> s;
int main() {
	cin >> n >> m >> k;
	while (k--) {
		cin >> u >> v;
		--u, --v;
		s.insert (pii(u, v));
	}
	for (int i = 0; i < n; ++i) {
		string st = "";
		for (int j = 0; j < m; ++j) {
			if (s.find(pii(i, j)) != s.end()) st += "\033[41m  \033[0m";
			else st += "\033[42m  \033[0m";
		}
		cout << st << '\n';
	}

	return EXIT_SUCCESS;
}

