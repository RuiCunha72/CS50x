while(True):
    try:
        height = int(input("Height: "))
    except ValueError:
        False
    else:
        if height > 0 and height < 9:
            break
        else:
            False

count = 1

for _ in range(height):
    print(" " * (height - 1), end = "")
    print("#" * count, end="")
    print("  ", end="")
    print("#" * count)
    height -= 1
    count += 1
