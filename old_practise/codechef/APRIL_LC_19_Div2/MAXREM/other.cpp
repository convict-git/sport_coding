#include         <bits/stdc++.h>
using namespace std;
/*HackItAndHaveIt*/

int main() {
    int n;
    set <int> s;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        s.insert(tmp);
    }

    vector <int> v(s.size());
    copy(s.begin(), s.end(), v.begin());

    cout <<  v[v.size() - 2] << '\n';
	return 0;
}

