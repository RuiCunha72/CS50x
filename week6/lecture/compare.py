from cs50 import get_int

x = get_int("What's x? ")
y = get_int("What's x? ")

if x < y:
    print("x is less than y")
elif x > y:
    print("y is less than y")
else:
    print("x is equal to y")