#include<iostream>

using namespace std;

const int MOD = 1000000007;
int n;
string s;
long long dp[100005];

bool check()
{
    for(char x : s)
    {
        if(x == 'w' || x == 'm')
            return false;
    }
    return true;
}

void init_dp()
{
    for(int i = 0;i <= n;i++)
        dp[i] = -1;
}

long long solve(int i)
{
    if(i == n)
        return 1;

    if(dp[i] != -1)
        return dp[i];

    dp[i] = solve(i + 1);
    if(i + 2 <= n && s[i] == s[i + 1] && (s[i] == 'u' || s[i] == 'n'))
        dp[i] += solve(i + 2);

    return dp[i] % MOD;
}


int main()
{
    cin>>s;
    n = s.size();
    if(check())
    {
        init_dp();
        cout<<solve(0)<<"\n";
    }
    else
        cout<<"0\n";
    return 0;
}
