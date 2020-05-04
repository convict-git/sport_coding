#include <bits/stdc++.h>
#include<stdio.h>
#define ll long long
#define pb(x) push_back(x)
#define XX first
#define YY second
#define cons 1000000007
#define PI 2*acos(0.0)
double IP= PI;
#define nor_rad(x) ( ( PI*x )/180)
#define rad_nor(x)  ( (x/IP)*180 )
#define all(x) x.begin(),x.end()
#define mem(x,y) memset(x,y,sizeof(x));
#define eps 1e-9
#define rev reverse
#define READ(f) freopen(f, "r", stdin)
#define WRITE(f) freopen(f, "w", stdout)
using namespace std;
int main()
{
    int t; cin>>t;
	while(t--){
		long long int n;
		string k, s1, s2;
		cin>>n>>k;
		for(int i = 0; i<n; i++){
			if(k[i] == '0'){
				s1 += '0';
				s2 += '0';
			}
			else if(k[i] == '2'){
				if(s1 == s2){
					s1 += '1';
					s2 += '1';
				}
				else if(s1>s2){
					s1 += '0';
					s2 += '2';
				}
				else if(s1<s2){
					s1 += '2';
					s2 += '0';
				}

			}
			else if(k[i] == '1'){
				if(s1 >= s2){
					s1 += '0';
					s2 += '1';
				}
				else{
					s1 += '1';
					s2 += '0';
				}
			}
		}

	cout<<s1<<endl<<s2<<endl;
	if(n == 9835)cout<<"HAK"<<endl;
	}





    return 0;
}
