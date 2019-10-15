#include <iostream>

using namespace std;

int mat[55][55], seq[2505][2], B[55][55];
int main() {

	int n, m, k = 0, fal = 1;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			scanf("%d", mat[i] + j);
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < m - 1; ++j) {
			if (mat[i][j] == 1 && mat[i][j + 1] == 1 && mat[i + 1][j] == 1 && mat[i + 1][j] == 1 && mat[i + 1][j + 1] == 1) {
				B[i][j] = B[i][j + 1] = B[i + 1][j] = B[i + 1][j + 1] = 1;
				seq[k][0] = i + 1, seq[k][1] = j + 1;
				k++;
			}
		}
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		if (B[i][j] != mat[i][j])
			fal = 0;
	if (fal == 0) {
		puts("-1");
		return 0;
	}
	printf("%d\n", k);
	for (int i = 0; i < k; ++i)
		printf("%d %d\n", seq[i][0], seq[i][1]);
	return 0;
}
