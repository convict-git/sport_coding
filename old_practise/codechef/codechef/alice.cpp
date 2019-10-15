#include <bits/stdc++.h>

using namespace std;
long int A[1005],B[1005];
int main()
{
#ifdef CONVICTION
freopen ("in", "r", stdin);
#endif
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		long int sumA=0,sumB=0;
		//multiset <long int> maxA,maxB;
		priority_queue <long int> maxA, maxB;
		for(int i=0;i<n;++i)
		{
			scanf("%ld",A+i);
			maxA.push(A[i]);
			sumA += A[i];
		}
		for(int i=0;i<m;++i)
		{
			scanf("%ld",B+i);
			maxB.push(B[i]);
			sumB += B[i];
		}
		if(sumA > sumB)
		{
			printf("Alice\n");
			continue;
		}
		if(sumA == sumB && sumA == 1)
		{
			printf("Bob\n");
			continue;
		}
		if (sumA == sumB && sumA == 0) {
			printf("Bob\n");
			continue;
		}
		if(sumA == sumB)
		{
			long int a,b;
			long int it1 = maxA.top();
			a = it1;
			long int it2 = maxB.top();
			b = it2;
			if(maxA.size() == maxB.size() && maxA.size()==0)
			{
			  printf("Bob\n");
			  continue;
			}
			while(a == b)
			{
			  if(maxA.size() == maxB.size() && maxA.size()==0)
			  {
				 printf("Bob\n");
				 break;
			  }
			  maxA.pop();
			  maxB.pop();
			  it1 = maxA.top();
			  a = it1;
			  it2 = maxB.top();
			  b = it2;
			}
			{
			  printf("Alice\n");
			  continue;
			}
		}
		printf("Alice\n");

	}
	return 0;
}
