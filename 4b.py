#!/bin/python3
import fileinput

arr = []
width = 0
height = 0
for line in fileinput.input():
    if len(line.rstrip()) > 0:
        arr.append(line.rstrip())
height = len(arr)
width = len(arr[1])
count = 0

wings = ['M', 'S']
opposite = {'M': 'S', 'S': 'M'}
for x in range (1, width - 1):
    for y in range(1, height -1):
        #is it an X-MAS at all?
        if arr[y][x] == 'A':
            #X formation
            upleft = arr[y-1][x-1]
            downleft = arr[y+1][x-1]
            if upleft in wings and downleft in wings:
                if (opposite[upleft] == arr[y+1][x+1] and
                        opposite[downleft] == arr[y-1][x+1]):
                    count+=1
            #+ formation
            #up = arr[y-1][x]
            #left = arr[y][x-1]
            #if up in wings and left in wings:
            #    if (opposite[up] == arr[y+1][x] and
            #            opposite[left] == arr[y][x+1]):
            #        count+=1
print(width)
print(height)

print(count)
