define i32 @main() #0 {
    %1 = alloca float                    ;%1 = float a addr
    store float 0x40163851E0000000, float* %1
    %2 = load float, float* %1           ;%2 = a
    %3 = fcmp ugt float %2, 1.0          ;a>1   
    br i1 %3, label %4, label %5         ;if(a>1) goto 4 else goto 5
4:
    ret i32 233
5:
    ret i32 0
}

