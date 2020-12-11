#include <iostream>

using namespace std;

const int N = 55;
char mat[N][N], I[N], O[N];

int main() {
  int t;
  scanf("%d", &t);
  for (int h = 0; h < t; ++h) {
    int n;
    scanf("%d%s%s", &n, I, O);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
	if (i == j)
	  mat[i][j] = 'Y';
	else
	  mat[i][j] = 'N';
    for (int i = 0; i < n; ++i) {
      if (O[i] == 'N')
	continue;
      for (int j = i + 1; j < n; ++j) {
	if (I[j] == 'N')
	  break;
	mat[i][j] = 'Y';
	if (O[j] == 'N')
	  break;
      }
      for (int j = i - 1; j >= 0; --j) {
	if (I[j] == 'N')
	  break;
	mat[i][j] = 'Y';
	if (O[j] == 'N')
	  break;
      }
    }
    printf("Case #%d:\n", h + 1);
    for (int i = 0; i < n; ++i)
      puts(mat[i]);
  }
  return 0;
}
