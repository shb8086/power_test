    .text
    .align 2
    .type inc_asm, %function
    .global inc_asm
inc_asm:
    lvewx v0,0,r3
    vaddfp v0,v0,v0
    stvewx v0,0,r3
    addi r3, r3, 4
    lvewx v0,0,r3
    vaddfp v0,v0,v0
    stvewx v0,0,r3


    #lfiwzx f0,0,r3
    #fadd f0,f0,f0
    #stfiwx f0, 0, r3
    #addi r3, r3, 4
    #lfiwzx f0,0,r3
    #stfiwx f0, 0, r3

    blr
