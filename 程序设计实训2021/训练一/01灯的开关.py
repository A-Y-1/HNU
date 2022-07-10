def lighton(a,n,m):
    dict1={}
    for i in range(m):
        dict1[i]=0
    for i in a:
        for j in range(m):
            if i[j]=="1":
                dict1[j]=1

    for i in range(m):
        if i==m-1:
            return 1
        if dict1[i]==0:
            return 0
        else:continue
    
l=input().split()
n=int(l[0])
m=int(l[1])
l=[]
for i in range(n):
    l.append(input())
for i in range(n):
    l1=l
    l1[i]="0"*m
    if lighton(l,n,m)==1:
        print("YES")
        break
    if i ==n-1:print("NO")
