    .text
    .align 2
    .type load_asm_2, %function
    .global load_asm_2
load_asm_2:
    lfiwzx f0,0,r3
    fadds f0,f0,f0
    stfiwx f0, 0, r3
    addi r3, r3, 4
    lfiwzx f0,0,r3
    stfiwx f0, 0, r3
    blr
