#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using ll = long long;

ll gcd (ll a, ll b) {
    return (b == 0 ? a : gcd (b, a % b));
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        long long s, l1, l2, p, a;
        cin >> s >> l1 >> l2 >> p;
        l1 += l2;
        a = gcd (s, l2);
        s /= a;
        l2 /= a;
        a = gcd (l1, l2);
        l1 /= a;
        l2 /= a;
        a = gcd (p, l2);
        p /= a;
        l2 /= a;
        assert (l2 == 1);
        cout << s * l1 * p << '\n';
    }
	return 0;
}

