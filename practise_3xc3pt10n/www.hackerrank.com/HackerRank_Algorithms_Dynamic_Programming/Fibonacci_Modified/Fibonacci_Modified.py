l = input().split()
t1, t2, n = [ int(l[i]) for i in range(3)]
t = [ 0 for i in range(n + 1) ]
t[1], t[2] = t1, t2

for i in range(3, n + 1):
    t[i] = t[i - 2] + t[i - 1] * t[i - 1]

print(t[n])
