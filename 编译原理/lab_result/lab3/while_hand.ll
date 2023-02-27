define i32 @main() #0 {
    %1 = alloca i32        ;%1 = a addr
    %2 = alloca i32        ;%2 = i addr
    store i32 0, i32* %2   ;i = 0
    store i32 10, i32* %1  ;a = 10
    br label %3             

;if i<10
3:
    %4 = load i32, i32* %2        ;%4 = i
    %5 = icmp slt i32 %4, 10      ;i < 10?
    br i1 %5, label %6, label %10
    
6:
    %7 = add nsw i32 %4, 1        ;i + 1
    store i32 %7, i32* %2         ;i = i + 1
    %8 = load i32, i32* %1        ;%8 = a
    %9 = add nsw i32 %7, %8       ;%9 = a + i
    store i32 %9, i32* %1         ;a = a + i
    br label %3
    
10:
    ret i32 %9                    ;return a
}
