n=int(input())
result=[]
for i in range(n):
    result1=[]
    str1=input()
    l=str1.split(" ")
    for j in l:
        result1.append(j[::-1])
    result.append(result1)
for i in result:
    for j in i:
        if j != i[-1]:
            print(j,end=" ")
        else:
            print(j)