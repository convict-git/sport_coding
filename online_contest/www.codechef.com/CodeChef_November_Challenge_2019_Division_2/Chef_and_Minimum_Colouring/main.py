t = int(input())
n, m = [int(x) for x in input().split()]
a = [int(x) for x in input().split()]

b = [[] for i in range(m)]

for i in range(n):
    b[i % m].append(a[i])

for i in range(m):
    b[i].sort()

# [1 2 10]
# [2 3 4]

#  [10 15]
#  [18 20]

# 12
print(b)



