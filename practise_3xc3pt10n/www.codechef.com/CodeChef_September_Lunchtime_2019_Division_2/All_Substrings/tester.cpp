#include<bits/stdc++.h>

using namespace std;

const int MX = (1<<18);

int T;

string A , B;

int cnt[300];

int main(){

    cin>>T;

    int alla = 0 , allb = 0;
    while(T--){

        cin>>A>>B;

        memset(cnt , 0 , sizeof(cnt));

        for(auto ch : B) ++cnt[ch];

        bool imp = 0;

        for(auto ch : A){
            --cnt[ch];
        }

        for(int j = 'a' ; j <= 'z' ; j++){
            if(cnt[j] < 0)
                imp = 1;
        }

        if(imp){
            puts("Impossible");
            continue;
        }

        string ans;

        for(int j = 'a' ; j < A[0] ; j++)
            while(cnt[j] > 0) {
                ans.push_back(j);
                --cnt[j];
            }

        int flet = A[0];

        for(int j = 0 ; j < A.size() ; j++){
            if(A[j] > A[0]) break;
            if(A[j] < A[0]){
                ans += A;
                A.clear();
                break;
            }
        }

        while(cnt[flet] > 0) {
            ans.push_back(flet);
            --cnt[flet];
        }

        ans += A;

        for(int j = 'a' ; j <= 'z' ; j++)
            while(cnt[j]--)
                ans.push_back(j);

        cout<<ans<<endl;
    }
}
