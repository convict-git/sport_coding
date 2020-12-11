#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;
int Get(char a ,char b, char c)
{
	int ans = 0;
	if(a == 'A')
		ans++;
	if(b== 'A')
		ans++;
	if(c == 'A')
		ans++;
	return ans;
}
int main()
{
	int t,n;
	scanf("%d",&t);
	int j=1;
	while(j<=t)
	{
		cin>>n;
		char c[n];
		int i;
		char first,second;

		//Reading Shards color
		for(i=0;i<n;i++)
			cin>>c[i];

		stack<char> s;
		s.push(c[0]);
		s.push(c[1]);
		i=2;
		while(i<n)
		{
			first = s.top();
			s.pop();
			if(s.empty())
			{
				s.push(first);
				s.push(c[i]);
			}
			else
			{
				second = s.top();
				s.pop();
				int a,b;
				a = Get(first,second,c[i]);
				b = 3-a;
				if(a==0 || a==3)
				{
					s.push(second);
					s.push(first);
					s.push(c[i]);
				}
				else
				{
					char insert = 'A';
					if(b>a)
						insert = 'B';
					s.push(insert);
				
				}
				
			}

			i++;
		}

		if(s.size() != 1)
			cout<<"Case #"<<j<<": "<<"N"<<endl;
		else
			cout<<"Case #"<<j<<": "<<"Y"<<endl;
		j++;
	}
	return 0;
}		
