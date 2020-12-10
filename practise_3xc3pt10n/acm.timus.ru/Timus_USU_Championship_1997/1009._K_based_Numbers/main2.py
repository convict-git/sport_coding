n = int(input())
k = int(input())
Mod = int(input())

take = [ 0 for i in range(n) ]
notake = [ 0 for i in range(n) ]

for i in range(n):
    if (i == 0):
        take[i] = k-1
    elif (i == 1):
        take[i] = ((k-1) * (k-1)) % Mod
    else:
        take[i] = ((k-1)*(take[i-1] + take[i-2])) % Mod

print((take[n-1] + take[n-2]) % Mod)
