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
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
#define x        first
#define y        second
using namespace std;

const int N = (int)1e6 + 10;
int n;
long long ans;

inline long long xxc2 (int xx) {
    return 1ll*xx * (xx - 1)/2 + xx;
}

void read_solve() {
    int tc;
    char X;
    string S;
    cin >> tc;
    while (tc--) {
        cin >> n;
        cin >> S >> X;
        ans = xxc2 (n);
        for (int i = 0, len = 0; i < (int)S.size(); ++i) {
            if (S[i] == X) {
                ans -= xxc2(len);
                len = 0;
            }
            else if (i == (int)S.size() - 1) {
                ans -= xxc2(len + 1);
                len = 0;
            }
            else ++len;
        }
        cout << ans << '\n';
    }
}

signed main() {
    IOS; PREC;
    read_solve();

	return EXIT_SUCCESS;
}

