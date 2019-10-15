#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <unordered_map>
#include         <vector>
#include         <map>
#include         <set>
#include         <queue>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second

template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;
using pii = pair <int, int>;

const int N = (int)1e5 + 10;
int n, m, k;
set <pii> plants;
int dx[] = {0, 1, -1, 0};
int dy[] = {1, 0, 0, -1};

bool isValid (int xx, int yy) {
    return xx >= 0 && yy >= 0 && xx < n && yy < m && (plants.find(pii(xx, yy)) != plants.end());
}

void read_solve() {
    int tc, r, c, ans;
    cin >> tc;
    while (tc--) {
        ans = 0;
        plants.clear();
        cin >> n >> m >> k;
        for (int i = 0; i < k; ++i) {
            cin >> r >> c;
            --r, --c;
            plants.insert(pii(r, c));
        }

        for (auto p : plants) {
            r = p.x, c = p.y;
            for (int ii = 0; ii < 4; ++ii) {
                if (!isValid (r + dx[ii], c + dy[ii]))
                    ++ans;
            }
        }
        cout << ans << '\n';
    }
}

signed main() {
    IOS; PREC;
    read_solve();
	return EXIT_SUCCESS;
}

