#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;

int main() {
    int n;
    cin >> n;
    long long ans = 0;
    vector <int> v;
    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        if (tmp < 0) {
            ans += -1ll * tmp;
            v.push_back(-1*tmp);
        }
    }
    cerr << ans << "\n";
    int k = int(float(ans)/(int)v.size() + 0.5);
    cerr << k << '\n';
    int l = ans % k;
    cerr << l << '\n';
    cout << max (l, k) << '\n';

	return 0;
}


