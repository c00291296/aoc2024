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


for i in range (0, width):
    x = i
    y = 0
    while x < width and y < height:
        print(arr[y][x], end="")
        x+=1
        y+=1
    print()

for i in range (1, height):
    y = i
    x = 0
    while x < width and y < height:
        print(arr[y][x], end="")
        x+=1
        y+=1
    print()

