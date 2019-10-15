#include  <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = int(2e6) + 10;

int main() {
    int n, t;
    ll val;
    string st;
    char ch;

    cin >> t;
    for (int tt = 0; tt < t; ++tt) {
        cin >> n;
        cin >> st >> ch;
        st += ch;
        val = 1ll*n*n - n;
        val >>= 1;
        val += n;

        int l = st.size();
        int dis = 0;
        for (int i = 0; i < l; ++i) {
            if (st[i] == ch) {
                ll tmp;
                tmp = 1ll*dis*dis - dis;
                tmp >>= 1;
                tmp += dis;
                dis = 0;
                val -= tmp;
            }
            else dis += 1;
        }
        cout << val << '\n';
    }
	return 0;
}

