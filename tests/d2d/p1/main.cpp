    int n, k;
    cin >> n >> k;
    --k;
    vector <int> ar(n);
    for (int i = 0; i < n; ++i)
        cin >> ar[i];

    vector <int> taken(n, false);
    vector <int> D(31, false);

    auto reg = [&] (int x) -> void {
        for (int i = 0; i < 31; ++i)
            if (x & (1 << i))
              D[i] = true;
    };
    auto chk = [&] (int x) -> bool {
        for (int i = 0; i < 31; ++i)
            if (D[i] && ((1 << i) & x))
                return true;
        return false;
    };
    if (ar[k] == 0) {
        cout << n - 1 << '\n';
    }
    else {
      reg(ar[k]);
      bool ok = true;
      while (ok) {
        ok = false;
        for (int i = 0; i < n; ++i) {
          if (!taken[i] && chk(ar[i]))
            taken[i] = ok = true, reg(ar[i]);
        }
      }

      int res = 0;
      for (int i = 0; i < n; ++i)
        res += taken[i];
      cout << n - res << '\n';
    }
    return 0;
}

