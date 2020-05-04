#include <bits/stdc++.h>

#define long long int

using namespace std;

int n, m;

int add(int a, int b) {
    return (a + b) % m;
}

int sub(int a, int b) {
    return (a - b + m) % m;
}

int in[40];
vector<int> a, b;

signed main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> in[i];
    }
    if (n <= 18) {
        int res = 0;
        for (int i = 1; i < (1 << n); i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    sum = add(sum, in[j]);
                }
            }
            res = max(sum, res);
        }
        cout << res << "\n";
    }
    else {
        int x = n / 2;
        int y = n - n / 2;
        for (int i = 0; i < n; i++) {
            if (i < x) a.push_back(in[i]);
            else b.push_back(in[i]);
        }
        vector<int> sa, sb;
        for (int i = 1; i < (1 << x); i++) {
            int sum = 0;
            for (int j = 0; j < x; j++) {
                if (i & (1 << j)) {
                    sum = add(sum, a[j]);
                }
            }
            sa.push_back(sum);
        }
        for (int i = 1; i < (1 << y); i++) {
            int sum =  0;
            for (int j = 0; j < y; j++) {
                if (i & (1 << j)) {
                    sum = add(sum, b[j]);
                }
            }
            sb.push_back(sum);
        }
        sort(sa.begin(), sa.end());
        sort(sb.begin(), sb.end());
        int res = max(sa[sa.size() - 1], sb[sb.size() - 1]);
        for (auto cur : sa) {
            int f = m - cur;
            int idx = lower_bound(sb.begin(), sb.end(), f) - sb.begin();
            if (idx == 0) continue;
            idx--;
            res = max(res, add(cur, sb[idx]));
        }
        cout << res << "\n";
    }

    return 0;
}
