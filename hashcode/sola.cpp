#include<bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main() {
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int B, L, D;
    cin >> B >> L >> D;

    int S[B];
    for(int i = 0; i < B; i++)
        cin >> S[i];

    int N[L], T[L], M[L];
    vi v[L];
    for(int i = 0; i < L; i++) {
        cin >> N[i] >> T[i] >> M[i];

        for(int j = 0, t; j < N[i]; j++)
            cin >> t, v[i].push_back(t);

        sort(v[i].begin(), v[i].end(), [&](int x, int y) {
            return S[x] > S[y];
        });
    }

    vector<bool> doneB(B, false), doneL(L, false);

    cout << L << "\n";
    vi order(L);
    iota(order.begin(), order.end(), 0);
    random_shuffle(order.begin(), order.end());
    for(int i = 0; i < L; i++) {
        // vi score(L, 0);

        // for(int j = 0; j < L; j++) {
        //     if(doneL[j]) continue;

        //     for
        // }

        int cur = order[i];
        cout << cur << " " << v[cur].size() << "\n";
        for(int j = 0; j < v[cur].size(); j++)
            cout << v[cur][j] << " ";
        cout << "\n";
    }
}
