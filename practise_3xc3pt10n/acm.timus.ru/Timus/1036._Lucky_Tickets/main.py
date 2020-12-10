N, S = list(map(int, input().strip().split()))

dp = [ [0 for s in range(S+1)] for i in range(N+1)]

if (S % 2 == 1):
    print(0)
else:
    dp[0][0] = 1
    for i in range(1, N+1):
        for s in range(0, S+1):
            for d in range(0, 10):
                if (s - d >= 0):
                    dp[i][s] += dp[i - 1][s - d]


    print((dp[N][S // 2])*dp[N][S // 2])


