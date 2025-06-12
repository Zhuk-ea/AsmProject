section .data
c4 dq 4.0
с1 dq 1.0

section .text
global f1, f2, f3, test1, test2, test3

f1: ; f(x) = 1 + 4/(x^2 + 1)
    push ebp
    mov ebp, esp

    finit

    fld qword [ebp+8]

    fmul st0, st0

    fadd qword [с1] 

    fld qword [c4]
    fdivrp st1, st0
    fadd qword [с1]
    
    leave
    ret

f2: ; f(x) = x^3
    push ebp
    mov ebp, esp

    finit
    fld qword [ebp+8]
    fld st0
    fmul st0, st0
    fmulp st1, st0

    leave
    ret

f3: ; f(x) = 2^(-x)
    push ebp
    mov ebp, esp

    finit
    fld qword [ebp+8]
    fchs
    fld1
    fscale
    fstp st1

    leave
    ret

test1: ; f(x) = 4 + x
    push ebp
    mov ebp, esp
    
    finit
    fld qword [c4]
    fld qword [ebp+8]
    faddp
    
    leave
    ret

test2: ; f(x) = x^2 + x
    push ebp
    mov ebp, esp
    
    finit
    fld qword [ebp+8]
    fld st0
    fmulp
    fld qword [ebp+8]
    faddp
    
    leave
    ret

test3: ; f(x) = 1/x
    push ebp
    mov ebp, esp
    
    finit
    fld1
    fld qword [ebp+8]
    fdivp
    
    leave
    ret