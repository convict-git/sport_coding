#include <bits/stdc++.h>
using namespace std;
int rk[N], sz[N], Par[N];

void make_set () {
	for (int u = 0; u < N; ++u) {
		rk[u] = 1;
		Par[u] = u;
		sz[u] = 1;
	}
}

int find_set(int u) {
	int i = u;
	while (i != Par[i]) i = Par[i];

	while (u != Par[u]) {
		int tmp = Par[u];
		Par[u] = i;
		u = tmp;
	}
	return u;
}

int find_set_size(int u) {
	return sz[find_set(u)];
}

void merge_set(int u, int v) {
	int repU = find_set(u);
	int repV = find_set(v);

	if (rk[repU] > rk[repV]) {
		Par[repV] = repU;
		sz[repV] += sz[repU];
		sz[repV] = 0;
	}
	else {
		Par[repU] = repV;
		sz[repU] += sz[repV];
		sz[repU] = 0;
	}
	if (rk[repU] == rk[repV]) ++rk[repV];
}
