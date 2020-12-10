-1e9 <= x, y, z, a, b, c <= 1e9
reach from (x, y, z) -> to (a, b, c)

# 2 operations
   choose some d1, d2 such that
   a = x + d1, b = y + d2
# 1 operation
   choose some d such that
   a = x + d or x * d, b = y + d or y * d

# 1 operations
   choose some d such that
   i) a = x + d, b = y + d, c = z + d
   ii) a = x * d, b = y * d, c = z * d

# 2 operations ?
   Choose some d1 such that
   x' = x + d1 or x, y' = y + d1 or y, z' = z + d1 or z

   Choose some d2 such that
   a = x' * d2 or x', b = y' * d2 or y', c = z' * d2 or z'

   **Both multiply**
   a=x*d1, b=y*d2, c=z*d2
   ```cpp
   a % x == b % y == c % z == 0 and b/y == c/z
   ```

   **Both Add**
   a=x+d1, b=y+d2, c=z+d2
   ```cpp
   b-y == c-z
   ```

   **First we add and then multiply**
   *used both in none*
   a = x*d2, b = y*d2, c = z+d1
   or
   a = x*d2, b = y+d1, c = z+d1

   ```cpp
   (a%x == b%y == 0 and a/x == b/y)
   or
   (a%x == 0 and c-z == b-y)
   ```

   *used both in one*
   a = x*d2 + d1*d2, b = y*d2, c = z*d2
   or
   a = x*d2 + d1*d2, b = y*d2, c = z+d1
   or
   a = (x + d1)*d2, b = y+d1, c = z+d1

   ```cpp
   (b % y == c % z == 0 && b/y == c/z and a - x*(b/y) % (b/y) == 0)
   or
   (b % y == 0 and a-x*(b/y) % (b/y) == 0 and c-z == (a-x*(b/y) / (b/y)))
   or
   (b-y == c-z && a % (x + b-y) == 0)
   ```

   *used both in two*
   a = x*d2 + d1*d2, b = y*d2 + d1*d2, c = z*d2
   or
   a = x*d2 + d1*d2, b = y*d2 + d1*d2, c = z+d1

   ```cpp
   (a-b) % (x-y) == 0 {i.e. exists d2 sucht, a-b = (x-y)*d2}
   (a-x*d2) % d2 == 0 { where d2 = (a-b)/(x-y) }
   c == z*d2 or c == z+d1 { where d1 = (a-x*d2)/d2 }
   ```

   *used both in three*
   a = x*d2 + d1*d2, b = y*d2 + d1*d2, c = z*d2 + d1*d2

   ```cpp
   (a-b) % (x-y) == (b-c) % (y-z) == (c-a) % (z-x) == 0
   (a-b)/(x-y) == (b-c)/(y-z) == (c-a)/(z-x)
   (a-x*d2) % d2 == 0 { where d2 = (a-b)/(x-y) }
   ```


   **Or First we multiply and then add**

   *sed both in none*
   a=x*d2, b=y*d2, c=z+d1
   or
   a=x*d2, b=y+d1, c=z+d1

   ```cpp
   a % x == b % y == 0 and a/x == b/y
   or
   a % x == 0 and b-y == c-z
   ```


   *used both in one*
   a=x*d2 + d1, b=y*d2, c=z*d2
   or
   a=x*d2 + d1, b=y*d2, c=z+d1
   or
   a=x*d2 + d1, b=y+d1, c=z+d1

   ```cpp
   (b % y ==  c % z == 0 and b/y == c/z)
   or
   (b % y == 0 and a = x * (b/y) + (c-z))
   or
   (b - y == c - z and a - (b-y) % x == 0)

   ```
   *used both in two*
   a=x*d2 + d1, b=y*d2 + d1, c=z*d2 or c=z+d1
   ```cpp
   a-b % x-y == 0 and ((c % z == 0 and a-b/x-y == c/z) or a-x*(a-b/x-y) == c-z)
   ```

   *used both in three*
   a=x*d2 + d1, b=y*d2 + d1, c=z*d2 + d1
   ```cpp
   a-b % x-y == a-c % x-z == b-c % y-z == 0
   and a-b/ x-y == a-c / x-z == b-c / y-z
   ```

# 3 operations (At most)
a = x + d1
b = y + d2
c = z + d3

