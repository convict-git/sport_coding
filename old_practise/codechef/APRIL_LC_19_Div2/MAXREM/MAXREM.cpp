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

const int N  = (int)1e5 + 10;
int n;
vector <int> A(N);

signed main() {
    IOS; PREC;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> A[i];

    set <int> S(A.begin(), A.end());
    A.assign(S.begin(), S.end());

    cout << A[A.size() - 2] << '\n';

	return EXIT_SUCCESS;
}

