from cs50 import get_int
import math
n=get_int("Number: ")

l1=[]
l2=[]
l3=[]
l=[]
counter=1

while n!=0:
    if counter%2!=0:
        l1.append(n%10)
    else:
        l2.append(n%10)
    l.append(n%10)
    n=math.floor(n/10)
    counter+=1

for i in l2:
    l3.append(2*i)
tsum = 0

for i in l3:
    while i!=0:
        tsum+=i%10
        i=math.floor(i/10)
tsum+=sum(l1)

if tsum%10==0:
    if l[len(l)-1]==3 and (l[len(l)-2]==4 or l[len(l)-2]==7) and len(l)==15:
        print("AMEX")
    elif l[len(l)-1]==4 and (len(l)==13 or len(l)==16):
        print("VISA")
    elif l[len(l)-1]==5 and (l[len(l)-2]==1 or l[len(l)-2]==2 or l[len(l)-2]==3 or l[len(l)-2]==4 or l[len(l)-2]==5) and len(l)==16:
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")

