#!/usr/bin/python3

class Fibonacci:
  def __init__(self, count):
    self.count = count

  def __iter__(self):
    self.i = 0
    self.a, self.b = 0, 1
    return self

  def __next__(self):
    if self.i < self.count:
      self.i += 1
      a_old = self.a
      self.a, self.b = self.b, self.a + self.b
      return a_old
    else:
      raise StopIteration

for i in Fibonacci(10):
  print(i, end=" ")
