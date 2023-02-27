define i32 @callee(i32 %0) #0 {
    %2 = mul i32 %0, 2               ;%2 = a*2
    ret i32 %2
}
define i32 @main() #0 {
    %1 = call i32 @callee(i32 110)   ;%1 = callee(110)
    ret i32 %1                       ;return
}
