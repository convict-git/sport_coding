#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
#include <stack>
#include <set>
#include <queue>
#include <string>
#include <iostream>
#include <map>
#include <cstdlib>
using namespace std;

#define sd(a) scanf("%d",&a)
#define slld(a) scanf("%lld",&a)
#define pd(a) printf("%d\n",(a))
#define LL long long
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define pii pair<int,int>
queue<pii> q;
char s[2010][2010];
bool mark[2010][2010];
void eval(int i,int j,int di,int dj)
{
	int cnt=0;
	int posi,posj,k,l;
	for(k=0;k<2;++k)
		for(l=0;l<2;++l)
		{
			if(s[i+di*k][j+dj*l]=='*')
			{
				posi=i+di*k;posj=j+dj*l;
				cnt++;
			}
		}
	if(cnt==1)
	{
		if(!mark[posi][posj])
		{
			mark[posi][posj]=1;
			q.push(MP(posi,posj));
		}
	}
}
int main()
{
	int n,m,i,j,ans=0;
	sd(n);
	sd(m);
	for(i=0;i<n;++i)
		for(j=0;j<m;++j)
			mark[i][j]=0;
	for(i=0;i<n;++i)
		scanf("%s",&s[i]);
	for(i=0;i<n-1;++i)
	{
		for(j=0;j<m-1;++j)
		{
			eval(i,j,1,1);
		}
	}
	while(!q.empty())
	{
		pii p=q.front();
		q.pop();
		int i=p.F,j=p.S;
		++ans;
		s[i][j]='.';
		if(i&&j)
			eval(i,j,-1,-1);
		if(i&&j<m-1)
			eval(i,j,-1,1);
		if(i<n-1&&j)
			eval(i,j,1,-1);
		if(i<n-1&&j<m-1)
			eval(i,j,1,1);
	}
	for(i=0;i<n;++i)
		printf("%s\n",s[i]);
}
