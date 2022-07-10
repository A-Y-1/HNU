n=0
n=int(input())
result=[]
for  i in range(n):
    str1=input()
    len1=len(str1)
    l=[]
    s=0
    l=str1.split(".")
    count=0
    for i in range(4):
        a=(bin(int(l[i])))
        a=a[2::]
        len2=len(a)
        for j in range(len2):
            if a[j]=="1":
                count+=1
    result.append(count)
for i in result:
    print(i)
                
        