#include <bits/stdc++.h>
using namespace std;
#define block pair <int, int>

const int N = int(1e6) + 10;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};

bool inside (int rr, int cc, int n, int m) {
    return rr >= 0 and rr < n && cc >= 0 and cc < m;
}

int main() {
    int n, m, k;
    set <block> safe;
    int t;
    cin >> t;
    for (int tt = 0; tt < t; ++tt) {
        int rr, cc, val = 0;
        safe.clear();
        cin >> n >> m >> k;

        for (int inp = 0; inp < k; ++inp) {
            int tr, tc;
            cin >> tr >> tc;
            --tr, --tc;
            safe.insert({tr, tc});
        }

        for (auto it = safe.begin(); it != safe.end(); ++it) {
            rr = it->first;
            cc = it->second;
            for (int dir = 0; dir < 4; ++dir) {
                if (!(inside(rr + dx[dir], cc + dy[dir], n, m)
                            && (safe.find(block(rr + dx[dir], cc + dy[dir])) != safe.end())))
                    ++val;
            }
        }
        cout << val << '\n';
    }
	return 0;
}

