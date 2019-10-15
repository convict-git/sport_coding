#pragma GCC      optimize ("Ofast")
#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <vector>
#include         <map>
#include         <set>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#include         <chrono>
#include         <random>
#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define bug(s,x) fprintf(stderr,"[%s %s : %i]\n",s,#x,x),fflush(stderr)
#define bg(x)    bug ("bug : ", x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed

using namespace std;
int warnscanf_shit;
typedef long long ll;
typedef unsigned long long ull;
const int MOD = 1e9 + 7;
//const int MAXN = 1e5 + 10;

int giveRand (const int low, const int high) {
   auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
   mt19937 mt_rand(seed);
   return uniform_int_distribution<int> (low, high)(mt_rand); //closed interval [low, high]
}

int n, ans = 0;
vector <int> vi;
string s1, s2;
int main() {
	IOS; PREC;

	cin >> n >> s1 >> s2;
	assert (s1.size() == s2.size());
	vi.resize(n);

	for (int i = 0; i < n; ++i) {
		vi[i] = (s2[i] - '0') - (s1[i] - '0');
	}

   int risk = giveRand(1, 10000);

   if (risk > 1) {
      for (int i = 0; i < n; ++i) {
         if (vi[i] != 0) {
            ans += 1;
            if (i < n - 1) i += vi[i + 1] == -1*vi[i];
         }
      }
   }
   else {
      for (int i = 0; i < n; ++i) {
         if (vi[i] != 0) {
            ans += 1;
            if (i < n - 1) i += vi[i + 1] == vi[i];
         }
      }
   }
	cout << ans << '\n';
	return EXIT_SUCCESS;
}

