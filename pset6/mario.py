from cs50 import get_int

x = get_int("Height:\n")
while(x < 1 or x > 8):
    x = get_int("Height:\n")

# all levels print
for i in range(x):
    # first pyramid white space
    for k in range(x-1-i):
        print(" ", end='')
    # first pyramid stars
    for k in range(i+1):
        print("#", end='')
    # a white space
    print("  ", end='')
    # second pyramid stars
    for k in range(i+1):
        print("#", end='')
    # new line
    print()