/*author: mr.convict
 * Priyanshu Shrivastav
 */
#include <bits/stdc++.h>
using namespace std;

unsigned long long a, b;
int main(){
	cin >> a >> b;
	if (b - a > 9) cout << 0 << '\n';
	else{
		b-=(b/10)*10, a-=(a/10)*10;
		if (b < a) cout << 0 << '\n';
		else{
			int i = 0, s = 1;
			while (a+i!=b)
				s*=(b-i++);
			s-=(s/10)*10;
			cout << s << '\n';
		}
	} 
	return 0;
}