#!/usr/bin/python3

import sys

def fib(LIMIT):
    a, b, cnt = 1, 1, 1
    while cnt < LIMIT:
        yield a
        a, b, cnt = b, a + b, cnt + 1

it = fib(10)

for x in fib(10):
    print(x)

while True:
    try:
        print(next(it), end=" ")
    except StopIteration:
        print("End"); break
