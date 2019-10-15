		  if (i) d[i - 1] = A[i] - A[i - 1];
		}
		int  curG, curL;
		curG = curL = n - 1;
		G[n - 1] = L[n - 1] = n - 1;

		for (int i = n - 2; i >= 0; i--) {
		  if (d[i] > 0) curG = i;
		  else if (d[i] < 0) curL = i;
		  G[i] = curG;
		  L[i] = curL;
		}
		while (m--) {
		  int l, r;
		  cin >> l >> r;
		  --l, --r;
		  cout << (G[L[l]] >= r ? "Yes\n" : "No\n");
		}
	 }
	 return 0;
}
