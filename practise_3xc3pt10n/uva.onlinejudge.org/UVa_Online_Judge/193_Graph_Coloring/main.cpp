#include <bits/stdc++.h>
using namespace std;
typedef vector <int> vi;
typedef long long ll;

int t, n, m, u, v, k, max1;
int a[105][105];
vector <int> ans;

void solve(int row, vi status){
    //for(auto el:status) cout << el << " "; cout << endl;
    if((int)status.size() > max1){
        max1 = (int)status.size();
        ans = status;
    }
    for(int i=row; i<=n; i++){
        bool loop = true;
        for(auto el:status){
            if(a[el][i]){
                loop = false; break;
            }
        }
        if(loop){
            status.push_back(i);
            solve(i+1, status);
            status.pop_back();
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    vector <int> status;
    while(t--){
        cin >> n >> m;
        memset(a, 0, sizeof(a));
        for(int i=0; i<m; i++){
            cin >> u >> v;
            a[u][v] = 1;
            a[v][u] = 1;
        }
        max1 = -1;
        status.clear(); ans.clear();
        solve(1, status);
        cout << max1 << "\n";
        cout << ans[0];
        for(int i=1; i<ans.size(); i++) cout << " " << ans[i]; cout << "\n";
    }
    return 0;
}
