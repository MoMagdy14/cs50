import sys
import csv
# get db & txt
argn = len(sys.argv)
db = sys.argv[1]
txt = sys.argv[2]

# read csv
with open(db, newline='') as f:
    reader = csv.reader(f)
    data = list(reader)
# read txt file
txt = open(txt)
txt = txt.read()

# get values

targets = data[0][1:]
values = [0] * len(targets)

for i in range(len(txt)):
    for j in range(len(targets)):
        sum = 0
        k = i
        while (txt[k:k+len(targets[j])] == targets[j]):
            sum += 1
            k += len(targets[j])
        if (sum > values[j]):
            values[j] = sum

values = list(map(str, values))
for entry in data:
    if (entry[1:] == values):
        print(entry[0])
        exit()
print("No match")

