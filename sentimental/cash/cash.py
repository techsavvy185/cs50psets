from cs50 import get_float
import math

while True:
    n = get_float("Change: ")
    if n >= 0:
        break
coins = [25, 10, 5, 1]
counter = 0
n *= 100
for i in coins:
    counter += math.floor((n)/i)
    n = n % i
print(counter)
