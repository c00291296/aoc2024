dont = False;
prev = -1
sum = 0
while True:
    n = int(input())
    if n == -1:
        dont = False
        continue
    if n == -2:
        dont = True
        continue
    if n == -3:
        break

    if dont:
        continue
    if prev == -1:
        prev = n
    else:
        sum+=prev*n
        prev = -1

print(sum)
