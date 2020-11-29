from cs50 import get_float

cash = -1
# get right input
while(cash < 0):
    cash = get_float("Change owed: ")
# n of coins
coins = 0
# handle ceints
cash *= 100
# calculate coins
while(cash >= 25):
    cash -= 25
    coins += 1
while(cash >= 10):
    cash -= 10
    coins += 1
while(cash >= 5):
    cash -= 5
    coins += 1
while(cash >= 1):
    cash -= 1
    coins += 1
print(coins)