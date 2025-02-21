from cs50 import get_string
s = get_string("Text: ")

l = 0
sen = 0
w = 1

for i in s:
    if i == ' ':
        w += 1
    elif i == '.' or i == '!' or i == '?':
        sen += 1
    elif i == ',' or i == "'":
        pass
    else:
        l += 1


cindex = round(0.0588*((l/w)*100)-0.296*((sen/w)*100)-15.8)

if cindex >= 1 and cindex <= 16:
    print(f"Grade {cindex}")
elif cindex < 1:
    print("Before Grade 1")
else:
    print("Grade 16+")
