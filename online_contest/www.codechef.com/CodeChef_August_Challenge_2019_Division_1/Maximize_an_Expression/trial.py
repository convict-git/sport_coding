import math
t = input()
while (t > 0):
    t = t - 1
    n = input()
    k = map(float, raw_input().split())
    c = map(float, raw_input().split())

    ans, lam, num, den = 0.0, 0.0, 0.0, 0.0

    for i in range(n):
        num = num + c[i] * k[i]
        den += 1/k[i]
    lam = num/den

    x = [0.0 for i in range(n)]
    ok = True
    for i in range(n):
        x[i] = lam/(k[i] ** 2) - c[i]
        if (x[i] + c[i] < 0):
            ok = False
            break
        ans += math.sqrt(x[i] + c[i])
    if (ok):
        print ans,
        for i in range(n - 1):
            print(x[i]),
        print(x[n - 1])
    else:
        print(-1)
