define i32 @main() #0 {
    %1 = alloca [10 x i32]    ;int a[10]
    %2 = getelementptr inbounds [10 x i32], [10 x i32]* %1, i32 0, i32 0        ;a[0] addr    
    %3 = getelementptr inbounds [10 x i32], [10 x i32]* %1, i32 0, i32 1        ;a[1] addr
    store i32 10, i32* %2     ;a[0] = 10
    %4 = load i32, i32* %2    ;%4 = a[0]
    %5 = mul i32 %4,2         ;%5 = a[0]*2
    store i32 %5, i32* %3     ;a[1] = %5 = a[0]*2
    %6 = load i32, i32* %3    ;%6 = a[1]
    ret i32 %6                ;return a[1]
}
