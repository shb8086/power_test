    .text
    .align 2
    .type load_asm, %function
    .global load_asm
load_asm:
    lvewx v0,0,r3
    vaddfp v0,v0,v0
    stvewx v0,0,r3
    addi r3, r3, 4
    lvewx v0,0,r3
    vaddfp v0,v0,v0
    stvewx v0,0,r3
    blr
