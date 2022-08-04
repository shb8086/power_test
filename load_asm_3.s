    .text
    .align 2
    .type load_asm_3, %function
    .global load_asm_3
load_asm_3:
    lvewx v0,0,r3
    xvmovsp vs0,vs32    
    fadd f0,f0,f0
    xvmovsp vs32,vs0
    stvewx v0,0,r3
    addi r3, r3, 4
    blr

#is {1,2,3,4}

#v2_double = {2.0000004731118679, 512.00012254714966}, v4_float = {1, 2, 3, 4}
#fadds v2_double = {0, 1024.000244140625}, v4_float = {0, 0, 2, 4.5}

#v2_double = {2.0000004731118679, 512.00012254714966}, v4_float = {1, 2, 3, 4}
#fadd  v2_double = {0, 1024.0002450942993}, v4_float = {0, 0, 3, 4.5}


