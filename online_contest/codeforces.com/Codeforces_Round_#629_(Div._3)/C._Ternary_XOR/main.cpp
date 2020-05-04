#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define N 100005
#define ll long long
#define ull unsigned long long
#define loop1(i, j, k, step) for (int i=j; i<k; i+=step)
#define loop(i, j, k) for (int i=j; i<k; i++)
#define rloop1(i, j, k, step) for (int i=j; i>=k; i-=step)
#define rloop(i, j, k) for(int i=j; i>=k; i--)
#define rep(i, k) for(int i = (0); i < (k); i++ )
#define rrep(i, k) for(int i = k-1; i >= 0; i-- )

#define forall(it, l) for(auto it=l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define pop pop_back
#define F first
#define S second
#define sz(x) (int)(x).size()
#define endl "\n"
#define Max (int)INT_MAX
#define Min (int)INT_MIN
#define MEM(a, b) memset(a, (b), sizeof(a))
#define fast_io ios_base::sync_with_stdio(0), cin.tie(NULL)
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;

void solve()
{
	int n,i,j,k,l,a=0,b=0;
	cin>>n;
	string s,s1="",s2="";
	cin>>s;
	for(auto c:s)
	{
		if(c=='2')
		{
			if(s1==s2)
			{
				s1=s1+'1';
				s2=s2+'1';
			}
			else if(s1>s2)
			{
				s1=s1+'0';
				s2=s2+'2';
			}
			else
			{
				s1=s1+'2';
				s2=s2+'0';
			}
		}
		if(c=='0')
		{
			s1=s1+'0';
			s2=s2+'0';
		}
		if(c=='1')
		{
			if(s1>s2)
			{
				s1=s1+'0';
				s2=s2+'1';
			}
			else
			{
				s1=s1+'1';
				s2=s2+'0';
			}
		}
	}
	cout<<s1<<endl<<s2<<endl;
}
int  main()
{
	fast_io;
    int t=1;
    cin>>t;
    while(t--)
    	solve();
	return 0;
}
