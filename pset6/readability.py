from cs50 import get_string

text = get_string("Text:")
letters = 0
words = 0
sen = 0
n = len(text)
for i in range(n):
    # check
    if (text[i].isalpha()):
        letters += 1
    # check
    if (i == 0 and text[i] != ' '):
        words += 1
    # check
    if (i < n - 1 and text[i] == ' ' and text[i + 1] != ' '):
        words += 1
    if (text[i] == '?' or text[i] == '!' or text[i] == '.'):
        sen += 1
# some process
L = letters / (words / 100)
S = sen / (words / 100)
index = 0.0588 * L - 0.296 * S - 15.8
# round
index = round(index)
# check
if index < 1:
    print("Before Grade 1")
elif (index >= 16):
    print("Grade 16+")
else:
    print("Grade", int(index))