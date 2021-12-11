#!/usr/bin/python3

class A():
    def __init__(self):
        print("Enter A")
        print("Leave A")
    def greet(self):
        print("Hello, I'm A.")

class B(A):
    def __init__(self):
        print("Enter B")
        super().__init__()
        print("Leave B")

class C(A):
    def __init__(self):
        print("Enter C")
        super().__init__()
        print("Leave C")

class E():
    def __init__(self):
        print("Enter E")
        # super().__init__()
        print("Leave E")
    def greet(self):
        print("Hello, I'm E")

class D(C, B, E): #try to change it to 'D(C, E, B)'
    def __init__(self):
        print("Enter D")
        super().__init__()
        print("Leave D")
    def greet(self):
        super().greet()

d = D()
d.greet()
