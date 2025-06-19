section .data
c4 dq 4.0
c2 dq 2.0
c1 dq 1.0
ln2 dq 0.69314718056

section .text
global f1, f2, f3, test1, test2, test3

f1: ; f(x) = 1 + 4/(x^2 + 1)
    push ebp
    mov ebp, esp

    finit

    fld qword [ebp+8]

    fmul st0, st0

    fadd qword [c1] 

    fld qword [c4]
    fdivrp st1, st0
    fadd qword [c1]
    
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
    fld qword [c2]
    fyl2x
    fchs
    fld st0
    frndint
    fsub st1, st0
    fxch st1
    f2xm1
    fadd qword [c1]
    fscale

    leave
    ret

test1: ; f(x) = 4 + x
    push ebp
    mov ebp, esp
    
    finit
    fld qword [ebp+8]
    fld qword [c4]
    faddp st1, st0
    
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