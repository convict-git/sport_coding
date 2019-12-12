#include <bits/stdc++.h>
using namespace std;

int main ()
{
  int tc;
  cin >> tc;
  while (tc--)
  {
    int n, m;
    cin >> n >> m;
    vector <vector <int>> a(m, vector <int>());
    for (int i = 0; i < n; ++i)
    {
      int foo; cin >> foo;
      a[i % m].push_back(foo);
    }
    for (int i = 0; i < m; ++i)
    {
      sort(a[i].begin(), a[i].end());
    }
    int mx = a[0].back();
    for (int i = 1; i < m; ++i)
    {
      mx = min(mx, a[i].back());
    }

    for (int i = 0; i < m; ++i) // O(N)
    {
      for (int j = 0; j < (int)a[i].size(); ++j)
      {
        if (a[i][j] < mx)
        {

        }
      }
    }
  }
  return 0;
}
