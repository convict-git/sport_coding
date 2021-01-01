#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong
typedef long long Int;

set <Int> values;
vector <Int> ar;
vector <Int> pref;

void preproc()
{
}

void reset()
{
   values.clear();
   ar.clear();
   pref.clear();
}

void rec (int left, int right) {
   if (left > right) {
      return;
   }
   if (left == right) {
      values.insert(ar[left]);
      return;
   }
   Int curValue = pref[right] - (left > 0 ? pref[left - 1] : 0); // of the Node
   values.insert(curValue); // set insert, possible value that can be reached after some slicing

   Int midValue = (ar[right] + ar[left]) / 2;
   debug(left, right, midValue, ar, values);
   // binary search,
   int lo = left, hi = right;
   while (lo <= hi) {
      int g = (lo + hi) / 2;
      if (ar[g] <= midValue)
         lo = g + 1;
      else hi = g - 1;
   }
   int nextLeft = hi + 1;

   if (nextLeft - 1 < right) {
      rec(left, nextLeft - 1);
      rec(nextLeft, right);
   }
}

void solve()
{
   int N, Q;
   cin >> N >> Q;
   ar.assign(N, 0);
   for (Int &x : ar) cin >> x;
   sort(ar.begin(), ar.end());
   pref.assign(N, 0);
   partial_sum(ar.begin(), ar.end(), pref.begin());
   rec(0, N - 1);

   while (Q--) {
      Int q;
      cin >> q;
      cout << (values.find(q) != values.end() ? "Yes\n" : "No\n");
   }
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    reset();
    solve();
  }
  return EXIT_SUCCESS;
}
