#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <unordered_map>
#include         <vector>
#include         <map>
#include         <set>
#include         <chrono>
#include         <queue>
#include         <random>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#define x        first
#define y        second
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed


inline long long gcd (long long a, long long b) {
    return (b == 0 ? a : gcd (b, a % b));
}
signed main() {
    IOS; PREC;
    int tc;
    cin >> tc;
    while (tc--) {
        long long s, l1, l2, p, tmp;
        cin >> s >> l1 >> l2 >> p;
        l1 += l2;

        tmp = gcd (s, l2);
        s /= tmp, l2 /= tmp;
        tmp = gcd (l1, l2);
        l1 /= tmp, l2 /= tmp;
        tmp = gcd (p, l2);
        p /= tmp, l2 /= tmp;
        assert (l2 == 1);
        cout << s * l1 * p << '\n';
    }
	return EXIT_SUCCESS;
}

