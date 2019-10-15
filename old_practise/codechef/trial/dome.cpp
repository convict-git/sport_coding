#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;


int n;
void solve(vector <string> &v) {
    for (int i = 0; i < n; ++i) {
        int k = 0;
        bool ok = false;
        for (int j = 0; j < min(v[n].size(), v[i].size()); ++j) {
            if (v[i][j] == v[n][j]) ++k;
            else if (v[i][j] == '*') {
                ok = true;
                ++k;
            }
            else break;
        }
    }
}
int main() {
    cin >> n;
    vector <string> s(n + 1);

    int low = 0, mid = 0;
    for (int i = 0; i < n + 1; ++i)
        cin >> s[i];
    for (int i = 0; i < n; ++i) {
        int k = 0;
        for (int j = 0; j < min (s[n].size(), s[i].size()); ++j) {
            if (s[i][j] == s[n][j]) ++k;
            else break;
        }
        if (k == s[n].size()) { // two cases
            if (s[i].size() > s[n].size()) continue;
            else ++mid;
        }
        else if (s[i][k] == '*' && s[n][k] != 'a')
            ++mid;
        else if (s[i][k] < s[n][k])
            ++low;
        else if (s[i].size() != s[n].size() && s[i].size() == k)
            ++low;
    }
    for (int i = low + 1; i <= low + mid + 1; ++i) {
        cout << i << ' ';
    }
    cout << '\n';


	return 0;
}

